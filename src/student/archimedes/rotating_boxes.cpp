#include "rotating_boxes.h"

#include <string>

#include "SF_src/DemoHandler.h"
#include "student/vector.h"

namespace student::archimedes {

RotatingBoxes::RotatingBoxes()
    : time_step_(1.0f / 60.0f)
    , box_a_(Vector(3.0f, 5.0f, 0.0f), 1.0f, 4.0f, 0.25f)
    , box_b_(Vector(6.0f, 5.0f, 0.0f), 1.0f, 1.0f, 1.0f)
    , local_points_a_({Point(1.0f, 0.05f, 0.0f), Point(1.5f, 0.125f, 0.0f)})
    , local_points_b_({Point(0.1f, 0.1f, 0.0f), Point(-0.2f, 0.2f, 0.0f)})
{}

void RotatingBoxes::update(DemoHandler* handler)
{
  box_a_.Update(time_step_, 0.01f);
  box_b_.Update(time_step_, 0.01f);

  box_a_.Draw(handler);
  box_b_.Draw(handler);

  box_a_.ClearForces();
  box_b_.ClearForces();

  std::array<Point, 2> global_points_a = {
      box_a_.LocalToGlobal(local_points_a_[0]),
      box_a_.LocalToGlobal(local_points_a_[1])};
  std::array<Point, 2> global_points_b = {
      box_b_.LocalToGlobal(local_points_b_[0]),
      box_b_.LocalToGlobal(local_points_b_[1])};

  std::array<Vector, 2> velocities_a = {
      box_a_.GetVelocityAtPoint(global_points_a[0]),
      box_a_.GetVelocityAtPoint(global_points_a[1])};
  std::array<Vector, 2> velocities_b = {
      box_b_.GetVelocityAtPoint(global_points_b[0]),
      box_b_.GetVelocityAtPoint(global_points_b[1])};

  handler->drawPoint(global_points_a[0]);
  handler->drawPoint(global_points_a[1]);
  handler->drawPoint(global_points_b[0]);
  handler->drawPoint(global_points_b[1]);

  handler->drawLine(
      global_points_a[0], (global_points_a[0] + velocities_a[0]), Color::PINK);
  handler->drawLine(
      global_points_a[1], (global_points_a[1] + velocities_a[1]), Color::PINK);
  handler->drawLine(
      global_points_b[0], (global_points_b[0] + velocities_b[0]), Color::PINK);
  handler->drawLine(
      global_points_b[1], (global_points_b[1] + velocities_b[1]), Color::PINK);

  // should have just created a DrawVelocityAtPoint function... haha
  if (handler->keyTyped(' ')) {
    box_a_.AddAngularImpulse(1.0f);
    box_b_.AddAngularImpulse(1.0f);
  }
}

auto RotatingBoxes::getName() -> const std::string
{
  return "2D rotation with inertia";
}

auto RotatingBoxes::getInfo() -> const std::string
{
  return "Press Space to spin the rectangles with the same force";
}

}  // namespace student::archimedes