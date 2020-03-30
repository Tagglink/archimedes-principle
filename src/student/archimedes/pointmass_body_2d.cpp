#include "pointmass_body_2d.h"

#include <iostream>
#include <memory>
#include <vector>

#include "SF_src/DemoHandler.h"
#include "student/geometry.h"
#include "student/random.h"

namespace student::archimedes {

PointmassBody2D::PointmassBody2D(const std::vector<Pointmass>& pointmasses,
                                 const Color color)
    : pointmasses_()
    , faces_()
    , color_(color)
{
  InitializeBody(pointmasses);
  density_ = GetMass() / geometry::AreaOfConvexPolygonXY(GetShape());
}

PointmassBody2D::PointmassBody2D(const std::vector<Point>& points,
                                 const float density,
                                 const Color color)
    : pointmasses_()
    , faces_()
    , color_(color)
    , density_(density)
{
  std::vector<Pointmass> pointmasses;

  float area = geometry::AreaOfConvexPolygonXY(points);

  float total_mass = area * density;

  float average_mass = total_mass / points.size();

  for (int i = 0; i < points.size(); i++) {
    pointmasses.emplace_back(average_mass, points.at(i));
  }

  InitializeBody(pointmasses);
}

void PointmassBody2D::Update(float delta_time, float damp)
{
  UpdateBody(delta_time, damp);
}

void PointmassBody2D::Draw(DemoHandler* handler)
{
  for (auto face : faces_) {
    DrawTriangle(handler, face);
  }
}

auto PointmassBody2D::GetShape() -> std::vector<Point>
{
  std::vector<Point> returned_list;
  returned_list.reserve(pointmasses_.size());

  for (int i = 0; i < pointmasses_.size(); i++) {
    returned_list.push_back(
        GetPosition() + RotateLocalToGlobal(pointmasses_.at(i)->position));
  }

  return returned_list;
}

auto PointmassBody2D::GetTotalArea() -> float
{
  auto shape = GetShape();

  return geometry::AreaOfConvexPolygonXY(shape);
}

auto PointmassBody2D::GetDensity() -> float
{
  return density_;
}

auto PointmassBody2D::GetColor() -> Color
{
  return color_;
}

void PointmassBody2D::InitializeBody(const std::vector<Pointmass>& pointmasses)
{
  // Triangulate the faces for drawing
  faces_ = Triangulate(pointmasses.size());

  // Calculate the total mass and the center of mass
  // in the same pass
  float total_mass = 0.0f;
  Point center_of_mass = 0.0f;

  for (int i = 0; i < pointmasses.size(); i++) {
    Pointmass pointmass = pointmasses.at(i);
    total_mass += pointmass.mass;
    center_of_mass += pointmass.position * pointmass.mass;
  }

  SetMass(total_mass);
  center_of_mass *= GetInvertedMass();
  SetPosition(center_of_mass);

  // Calculate the local position of pointmasses and
  // the moment of inertia in the same pass
  float moment_of_inertia = 0.0f;
  for (int i = 0; i < pointmasses.size(); i++) {
    Pointmass pointmass = pointmasses.at(i);
    // offset the pointmass with the center of mass
    pointmass.position -= center_of_mass;
    // use the offset position to calculate the moment of inertia
    moment_of_inertia += pointmass.position.SquareMagnitude() * pointmass.mass;
    // copy it to a shared_ptr
    pointmasses_.push_back(std::make_shared<Pointmass>(pointmass));
  }

  SetMomentOfInertia(moment_of_inertia);
}

// Triangulate the polygon using a triangle fan
auto PointmassBody2D::Triangulate(int points_length) -> std::vector<Triangle>
{
  std::vector<Triangle> faces;
  faces.reserve(points_length - 2);

  for (int i = 0; i < points_length - 2; i++) {
    faces.push_back(  // cycle through colors
        Triangle(0, i + 1, i + 2, color_));
  }

  return faces;
}

void PointmassBody2D::DrawTriangle(DemoHandler* handler, Triangle triangle)
{
  handler->drawPolygon(
      {GetPosition()
           + RotateLocalToGlobal(pointmasses_.at(triangle.a)->position),
       GetPosition()
           + RotateLocalToGlobal(pointmasses_.at(triangle.b)->position),
       GetPosition()
           + RotateLocalToGlobal(pointmasses_.at(triangle.c)->position)},
      triangle.color);

  handler->drawPolygon(
      {GetPosition()
           + RotateLocalToGlobal(pointmasses_.at(triangle.a)->position),
       GetPosition()
           + RotateLocalToGlobal(pointmasses_.at(triangle.c)->position),
       GetPosition()
           + RotateLocalToGlobal(pointmasses_.at(triangle.b)->position)},
      triangle.color);
}

}  // namespace student::archimedes
