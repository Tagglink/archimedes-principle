#include "simulation.h"

#include <iostream>
#include <memory>
#include <string>

#include "SF_src/DemoHandler.h"
#include "student/archimedes/pointmass.h"
#include "student/archimedes/slicer.h"
#include "student/geometry.h"
#include "student/plane.h"
#include "student/vector.h"

namespace {

template <typename T>
auto Contains(const std::vector<T>& elements, const T& value) -> bool
{
  for (T element : elements) {
    if (element == value) {
      return true;
    }
  }

  return false;
}

}  // namespace

namespace student::archimedes {

Simulation::Simulation()
    : time_step_(1.0f / 60.0f)
    , damping_(0.00f)
    , bodies_()
    , liquids_()
    , gravity_acceleration_(9.82f)
    , user_force_(100.0f)
{
  InitializeSimulation();
}

void Simulation::update(DemoHandler* handler)
{
  for (int i = 0; i < liquids_.size(); i++) {
    SimulateLiquid(liquids_.at(i));
    liquids_.at(i)->Draw(handler);
  }

  for (int i = 0; i < bodies_.size(); i++) {
    bodies_.at(i)->AddForce(
        Vector(0.0f, -gravity_acceleration_, 0.0f) * bodies_.at(i)->GetMass(),
        bodies_.at(i)->GetPosition());
    bodies_.at(i)->Update(time_step_, damping_);
    bodies_.at(i)->Draw(handler);
    bodies_.at(i)->ClearForce();
  }

  static bool mouse_held_left = false;
  static bool mouse_held_middle = false;
  static Point mouse_left_click_position = 0.0f;
  static Point mouse_middle_click_position = 0.0f;

  // click-drag functionality for the left mouse button, slicing objects
  if (mouse_held_left) {
    handler->drawLine(mouse_left_click_position,
                      handler->getMouseLocation(),
                      Color::MAGENTA,
                      0.01f);
    if (!handler->isMouseDown() && bodies_.size() > 0) {
      HandleSlicing(mouse_left_click_position, handler->getMouseLocation());
      mouse_held_left = false;
    }
  } else if (!mouse_held_left && handler->isMouseDown()) {
    mouse_left_click_position = handler->getMouseLocation();
    mouse_held_left = true;
  }

  // click-drag functionality for the middle mouse button, pushing objects
  if (mouse_held_middle) {
    handler->drawLine(mouse_middle_click_position,
                      handler->getMouseLocation(),
                      Color::PINK,
                      0.01f);
    if (!handler->isMouseDown(Button::MIDDLE) && bodies_.size() > 0) {
      HandlePushing(mouse_middle_click_position, handler->getMouseLocation());
      mouse_held_middle = false;
    }
  } else if (!mouse_held_middle && handler->isMouseDown(Button::MIDDLE)) {
    mouse_middle_click_position = handler->getMouseLocation();
    mouse_held_middle = true;
  }

  // R resets
  if (handler->keyTyped('r')) {
    ResetSimulation();
  }

  if (handler->keyTyped('w')) {
    for (auto liquid : liquids_) {
      liquid->SetDensity(liquid->GetDensity() + 0.5f);
    }
  } else if (handler->keyTyped('s')) {
    for (auto liquid : liquids_) {
      liquid->SetDensity(liquid->GetDensity() - 0.5f);
    }
  }

  if (handler->keyTyped('e')) {
    damping_ += 0.01f;
    if (damping_ > 1.0f) {
      damping_ = 1.0f;
    }
  } else if (handler->keyTyped('d')) {
    damping_ -= 0.01f;
    if (damping_ < 0.0f) {
      damping_ = 0.0f;
    }
  }

  for (int i = 0; i < liquids_.size(); i++) {
    handler->drawText(
        Point(0.0f, 10.0f - (i * 0.5f), 0.0f),
        "liquid density: " + std::to_string(liquids_.at(i)->GetDensity()));
  }

  handler->drawText(
      Point(0.0f, 10.5f, 0.0f), "damping: " + std::to_string(damping_));
}

auto Simulation::getName() -> const std::string
{
  return "Simulation of archimedes principle";
}

auto Simulation::getInfo() -> const std::string
{
  return "Press W to increase liquid density, and S to decrease it.\n"
         "Press E to increase damping and D to decrease it.";
}

void Simulation::InitializeSimulation()
{
  auto body1 = std::make_shared<PointmassBody2D>(
      std::vector<Point>{Point(26.0f, 0.0f, 0.0f),
                         Point(25.0f, 0.0f, 0.0f),
                         Point(24.75f, 0.75f, 0.0f),
                         Point(25.5f, 1.5f, 0.0f),
                         Point(26.25f, 0.75f, 0.0f)},
      1.0f,
      Color::BLUE);
  auto body2 = std::make_shared<PointmassBody2D>(
      std::vector<Point>{Point(14.0f, 4.0f, 0.0f),
                         Point(16.0f, 4.0f, 0.0f),
                         Point(16.0f, 6.0f, 0.0f),
                         Point(14.0f, 6.0f, 0.0f)},
      2.0f,
      Color::YELLOW);
  auto body3 = std::make_shared<PointmassBody2D>(
      std::vector<Point>{Point(9.0f, 6.0f, 0.0f),
                         Point(8.0f, 4.0f, 0.0f),
                         Point(9.0f, 2.0f, 0.0f),
                         Point(10.0f, 4.0f, 0.0f)},
      3.0f,
      Color::RED);
  auto body4 = std::make_shared<PointmassBody2D>(
      std::vector<Point>{
          Point(2.0f, 0.0f, 0.0f),
          Point(4.0f, 0.0f, 0.0f),
          Point(6.0f, 2.0f, 0.0f),
          Point(6.0f, 4.0f, 0.0f),
          Point(4.0f, 6.0f, 0.0f),
          Point(2.0f, 6.0f, 0.0f),
          Point(0.0f, 4.0f, 0.0f),
          Point(0.0f, 2.0f, 0.0f),
      },
      4.0f,
      Color::GREEN);

  bodies_.push_back(body1);
  bodies_.push_back(body2);
  bodies_.push_back(body3);
  bodies_.push_back(body4);

  auto liquid1 = std::make_shared<LiquidBody2D>(
      31.0f, 40.0f, Point(15.0f, -55.0f, 0.0f), 4.2f);

  liquids_.push_back(liquid1);
}

void Simulation::ResetSimulation()
{
  bodies_.clear();
  liquids_.clear();

  InitializeSimulation();
}

void Simulation::SimulateLiquid(const std::shared_ptr<LiquidBody2D>& liquid)
{
  std::vector<std::shared_ptr<PointmassBody2D>> bodies_to_simulate;
  auto horizontal_bounds = liquid->GetHorisontalBounds();
  auto vertical_bounds = liquid->GetVerticalBounds();

  for (int i = 0; i < bodies_.size(); i++) {
    auto shape = bodies_.at(i)->GetShape();
    if (slicer::IsWithinBounds(
            horizontal_bounds[0], horizontal_bounds[1], shape)
        && slicer::IsWithinBounds(
            vertical_bounds[0], vertical_bounds[1], shape)) {
      bodies_to_simulate.push_back(bodies_.at(i));
    }
  }

  liquid->HandleBodies(bodies_to_simulate, gravity_acceleration_);
}

void Simulation::HandleSlicing(const Point& point_a, const Point& point_b)
{
  std::vector<std::shared_ptr<PointmassBody2D>> new_bodies;
  std::vector<int> erased_bodies;

  auto slicing_planes = GetSlicingData(point_a, point_b);

  for (int i = 0; i < bodies_.size(); i++) {
    std::vector<Point> polygon_shape = bodies_.at(i)->GetShape();

    if (slicer::IsStrictlyWithinBounds(
            slicing_planes[1], slicing_planes[2], polygon_shape)
        && slicer::Intersects(slicing_planes[0], polygon_shape)) {
      auto resulting_bodies = SliceBody(bodies_.at(i), slicing_planes[0]);

      erased_bodies.push_back(i);

      resulting_bodies[0]->SetAngularSpeed(bodies_.at(i)->GetAngularSpeed());
      resulting_bodies[0]->SetVelocity(
          bodies_.at(i)->GetVelocity(bodies_.at(i)->GetPosition()));
      resulting_bodies[1]->SetAngularSpeed(bodies_.at(i)->GetAngularSpeed());
      resulting_bodies[1]->SetVelocity(
          bodies_.at(i)->GetVelocity(bodies_.at(i)->GetPosition()));

      new_bodies.push_back(resulting_bodies[0]);
      new_bodies.push_back(resulting_bodies[1]);
    }
  }

  for (int i = 0; i < bodies_.size(); i++) {
    if (!::Contains(erased_bodies, i)) {
      new_bodies.push_back(bodies_.at(i));
    }
  }

  bodies_ = new_bodies;
}

void Simulation::HandlePushing(const Point& point_a, const Point& point_b)
{
  for (auto body : bodies_) {
    if (geometry::PointOverlapsConvexPolygonXY(point_a, body->GetShape())) {
      body->AddForce((point_b - point_a) * user_force_, point_a);
    }
  }
}

auto Simulation::SliceBody(
    const std::shared_ptr<PointmassBody2D>& body_to_slice,
    const Plane& slicing_plane)
    -> std::array<std::shared_ptr<PointmassBody2D>, 2>
{
  auto resulting_polys =
      slicer::SlicePolygon(body_to_slice->GetShape(), slicing_plane);

  return {std::make_shared<PointmassBody2D>(resulting_polys[0],
                                            body_to_slice->GetDensity(),
                                            body_to_slice->GetColor()),
          std::make_shared<PointmassBody2D>(resulting_polys[1],
                                            body_to_slice->GetDensity(),
                                            body_to_slice->GetColor())};
}

auto Simulation::GetSlicingData(Point slice_a, Point slice_b)
    -> std::array<Plane, 3>
{
  Vector slicing_line = slice_b - slice_a;
  Vector slicing_line_normal =
      Vector(-slicing_line.y, slicing_line.x, 0.0f).Normalized();
  Vector slicing_line_normalized = slicing_line.Normalized();

  Plane slicing_plane = Plane(slice_a, slicing_line_normal);
  Plane bounding_plane_a = Plane(slice_a, slicing_line_normalized);
  Plane bounding_plane_b = Plane(slice_b, -slicing_line_normalized);

  return {slicing_plane, bounding_plane_a, bounding_plane_b};
}

}  // namespace student::archimedes