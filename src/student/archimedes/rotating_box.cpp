#include "rotating_box.h"

namespace student::archimedes {

RotatingBox::RotatingBox(const Point& position,
                         float mass,
                         float width,
                         float height)
    : orientation_(0.0f)
    , angular_momentum_(0.0f)
    , torque_(0.0f)
    , position_(position)
    , width_(width)
    , height_(height)
    , local_corners_({Point(-width / 2, -height / 2, 0),
                      Point(width / 2, -height / 2, 0),
                      Point(width / 2, height / 2, 0),
                      Point(-width / 2, height / 2, 0)})
{
  moment_of_inertia_ = mass * (width * width + height * height) / 12.0f;
  inverted_moment_of_inertia_ = 1.0f / moment_of_inertia_;
}

auto RotatingBox::RotateLocalVector(const Vector& vector_to_rotate) -> Vector
{
  return Vector(vector_to_rotate.x * cosf(orientation_)
                    - vector_to_rotate.y * sinf(orientation_),
                vector_to_rotate.x * sinf(orientation_)
                    + vector_to_rotate.y * cosf(orientation_),
                0.0f);
}

auto RotatingBox::RotateGlobalVector(const Vector& vector_to_rotate) -> Vector
{
  return Vector(vector_to_rotate.x * cosf(-orientation_)
                    - vector_to_rotate.y * sinf(-orientation_),
                vector_to_rotate.x * sinf(-orientation_)
                    + vector_to_rotate.y * cosf(orientation_),
                0.0f);
}

auto RotatingBox::LocalToGlobal(const Point& local_point) -> Point
{
  return position_ + RotateLocalVector(local_point);
}

auto RotatingBox::GlobalToLocal(const Point& global_point) -> Point
{
  return RotateGlobalVector(global_point - position_);
}

void RotatingBox::ClearForces()
{
  torque_ = 0.0f;
}

void RotatingBox::AddForce(const Vector& force, const Point& global_point)
{
  Vector radius_vector = global_point - position_;
  torque_ += radius_vector.CrossProduct(force).z;
}

auto RotatingBox::GetVelocityAtPoint(const Point& global_point) -> Vector
{
  Vector angular_velocity = Vector(0.0f, 0.0f, GetAngularVelocity());
  Vector radius_vector = global_point - position_;
  return angular_velocity.CrossProduct(radius_vector);
}

auto RotatingBox::GetAngularVelocity() -> float
{
  return inverted_moment_of_inertia_ * angular_momentum_;
}

void RotatingBox::AddAngularImpulse(float delta_impulse)
{
  angular_momentum_ += delta_impulse;
}

void RotatingBox::Update(float delta_time, float damp)
{
  orientation_ += GetAngularVelocity() * delta_time;
  angular_momentum_ += torque_ * delta_time;
  angular_momentum_ *= (1.0f - damp);
}

void RotatingBox::Draw(DemoHandler* handler)
{
  handler->drawLine(
      LocalToGlobal(local_corners_[0]), LocalToGlobal(local_corners_[1]));
  handler->drawLine(
      LocalToGlobal(local_corners_[1]), LocalToGlobal(local_corners_[2]));
  handler->drawLine(
      LocalToGlobal(local_corners_[2]), LocalToGlobal(local_corners_[3]));
  handler->drawLine(
      LocalToGlobal(local_corners_[3]), LocalToGlobal(local_corners_[0]));

  handler->drawPoint(position_);
}

auto RotatingBox::Overlaps(const Point& global_point) -> bool
{
  Point local_point = GlobalToLocal(global_point);
  return (abs(local_point.x) <= width_ / 2)
         && (abs(local_point.y) <= height_ / 2);
}

}  // namespace student::archimedes