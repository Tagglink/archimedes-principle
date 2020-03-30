#include "liquid_body_2d.h"

#include "student/plane.h"
#include "student/archimedes/slicer.h"
#include "student/geometry.h"

namespace student::archimedes {

LiquidBody2D::LiquidBody2D(float width,
                           float height,
                           Point position,
                           float density)
    : width_(width)
    , height_(height)
    , position_(position)
    , density_(density)
    , height_extension_(0.0f)
    , surface_normal_(0.0f, 1.0f, 0.0f)
{}

// the input should only contain bodies that are within the liquid
void LiquidBody2D::HandleBodies(
    const std::vector<std::shared_ptr<PointmassBody2D>>& bodies,
    const float gravity_acceleration)
{
  Plane surface_plane = Plane(
      position_
          + Point(width_ * 0.5f, height_extension_ + (height_ * 0.5f), 0.0f),
      surface_normal_);

  float total_extension = 0.0f;

  for (int i = 0; i < bodies.size(); i++) {
    auto shape = bodies.at(i)->GetShape();
    float area = 0.0f;
    float buoyancy_strength = 0.0f;

    if (slicer::Intersects(surface_plane, shape)) {
      auto slice_result = slicer::SlicePolygon(shape, surface_plane);

      // since the surface normal always points upwards, we know that the back
      // result (1) of the slice is the result submerged in the liquid
      area = geometry::AreaOfConvexPolygonXY(slice_result[1]);
    } else {
      area = geometry::AreaOfConvexPolygonXY(shape);
    }

    // archimedes principle says that the weight of the liquid displaced by an
    // object is equivalent to the buoyant force on the object
    // in 2D, we pretend that volume <=> area
    buoyancy_strength = area * density_ * gravity_acceleration;

    bodies.at(i)->AddForce(
        Vector(0.0f, buoyancy_strength, 0.0f), bodies.at(i)->GetPosition());

    total_extension += area / width_;
  }

  height_extension_ = height_ + total_extension;
}

void LiquidBody2D::Draw(DemoHandler* handler)
{
  float half_width = width_ * 0.5f;
  float half_height = height_ * 0.5f;
  Color color = Color::CYAN;

  // bottom
  handler->drawLine(position_ + Point(-half_width, -half_height, 0.0f),
                    position_ + Point(half_width, -half_height, 0.0f),
                    color,
                    0.01f);
  // right
  handler->drawLine(
      position_ + Point(half_width, -half_height, 0.0f),
      position_ + Point(half_width, half_height + height_extension_, 0.0f),
      color,
      0.01f);
  // top
  handler->drawLine(
      position_ + Point(-half_width, half_height + height_extension_, 0.0f),
      position_ + Point(half_width, half_height + height_extension_, 0.0f),
      color,
      0.01f);
  // left
  handler->drawLine(
      position_ + Point(-half_width, -half_height, 0.0f),
      position_ + Point(-half_width, half_height + height_extension_, 0.0f),
      color,
      0.01f);
}

auto LiquidBody2D::GetHorisontalBounds() -> std::array<Plane, 2>
{
  Point bottom_left = position_ + Point(-width_ * 0.5f, -height_ * 0.5f, 0.0f);
  Point bottom_right = position_ + Point(width_ * 0.5f, -height_ * 0.5f, 0.0f);

  Plane left_plane = Plane(bottom_left, Vector(1.0f, 0.0f, 0.0f));
  Plane right_plane = Plane(bottom_right, Vector(-1.0f, 0.0f, 0.0f));

  return {left_plane, right_plane};
}

auto LiquidBody2D::GetVerticalBounds() -> std::array<Plane, 2>
{
  Point top_left =
      position_
      + Point(-width_ * 0.5f, height_extension_ + (height_ * 0.5f), 0.0f);
  Point bottom_left = position_ + Point(-width_ * 0.5f, -height_ * 0.5f, 0.0f);

  Plane top_plane = Plane(top_left, Vector(0.0f, -1.0f, 0.0f));
  Plane bottom_plane = Plane(bottom_left, Vector(0.0f, 1.0f, 0.0f));

  return {top_plane, bottom_plane};
}

}  // namespace student::archimedes
