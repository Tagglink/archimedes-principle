#include "student/archimedes/rigidbody_2d.h"

namespace student::archimedes {

Rigidbody2D::Rigidbody2D()
{
  orientation_ = 0.0f;
  angular_momentum_ = 0.0f;
  ClearForce();
}

void Rigidbody2D::SetPosition(const Point& position)
{
  position_ = position;
}

auto Rigidbody2D::GetPosition() -> Point
{
  return position_;
}

void Rigidbody2D::SetMass(float mass)
{
  mass_ = mass;
  inverted_mass_ = 1.0f / mass;
}

auto Rigidbody2D::GetMass() -> float
{
  return mass_;
}

auto Rigidbody2D::GetInvertedMass() -> float
{
  return inverted_mass_;
}

auto Rigidbody2D::GetInvertedMomentOfInertia() -> float
{
  return inverted_moment_of_inertia_;
}

void Rigidbody2D::SetMomentOfInertia(float moment_of_inertia)
{
  moment_of_inertia_ = moment_of_inertia;
  inverted_moment_of_inertia_ = 1.0f / moment_of_inertia;
}

auto Rigidbody2D::RotateLocalToGlobal(const Vector& local_vector) -> Vector
{
  return Vector(
      local_vector.x * cos(orientation_) - local_vector.y * sin(orientation_),
      local_vector.x * sin(orientation_) + local_vector.y * cos(orientation_),
      0.0f);
}

auto Rigidbody2D::RotateGlobalToLocal(const Vector& global_vector) -> Vector
{
  return Vector(global_vector.x * cos(-orientation_)
                    - global_vector.y * sin(-orientation_),
                global_vector.x * sin(-orientation_)
                    + global_vector.y * cos(-orientation_),
                0.0f);
}

void Rigidbody2D::ClearForce()
{
  force_ = 0.0f;
  torque_ = 0.0f;
}

void Rigidbody2D::AddForce(const Vector& force, const Point& global_point)
{
  torque_ += (global_point - position_).CrossProduct(force).z;
  force_ += force;
}

auto Rigidbody2D::GetVelocity(const Point& global_point) -> Vector
{
  return (momentum_ * inverted_mass_)
         + Vector(0.0f, 0.0f, GetAngularSpeed())
               .CrossProduct(global_point - position_);
}

void Rigidbody2D::SetVelocity(const Vector& velocity) {
  momentum_ = velocity * mass_;
}

auto Rigidbody2D::GetOrientation() -> float
{
  return orientation_;
}

void Rigidbody2D::SetOrientation(float orientation) {
  orientation_ = orientation;
}

auto Rigidbody2D::GetAngularSpeed() -> float
{
  return inverted_moment_of_inertia_ * angular_momentum_;
}

void Rigidbody2D::SetAngularSpeed(float angular_speed)
{
  angular_momentum_ = moment_of_inertia_ * angular_speed;
}

void Rigidbody2D::AddAngularImpulse(const Vector& impulse)
{
  angular_momentum_ += impulse.z;
}

void Rigidbody2D::UpdateBody(float delta_time, float damp)
{
  position_ += momentum_ * inverted_mass_ * delta_time;
  momentum_ += force_ * delta_time;
  momentum_ *= (1.0f - damp);

  orientation_ += GetAngularSpeed() * delta_time;
  angular_momentum_ += torque_ * delta_time;
  angular_momentum_ *= (1.0f - damp);
}
}  // namespace student::archimedes