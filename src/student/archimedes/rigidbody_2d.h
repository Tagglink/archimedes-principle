#ifndef RIGIDBODY_2D_H
#define RIGIDBODY_2D_H

#include "SF_src/DemoHandler.h"
#include "student/vector.h"

namespace student::archimedes {

class Rigidbody2D
{
  Point position_;
  Vector momentum_;
  Vector force_;
  float mass_;
  float inverted_mass_;

  // 2D specifics
  float orientation_;
  float angular_momentum_;
  float torque_;
  float moment_of_inertia_;
  float inverted_moment_of_inertia_;

public:
  Rigidbody2D();

  void SetPosition(const Point& position);
  auto GetPosition() -> Point;
  void SetMass(float mass);
  auto GetMass() -> float;
  auto GetInvertedMass() -> float;

  auto GetInvertedMomentOfInertia() -> float;
  void SetMomentOfInertia(float moment_of_inertia);
  auto RotateLocalToGlobal(const Vector& local_vector) -> Vector;
  auto RotateGlobalToLocal(const Vector& global_vector) -> Vector;
  void ClearForce();
  void AddForce(const Vector& force, const Point& global_point);
  auto GetVelocity(const Point& global_point) -> Vector;
  void SetVelocity(const Vector& velocity);
  auto GetOrientation() -> float;
  void SetOrientation(float orientation);
  auto GetAngularSpeed() -> float;
  void SetAngularSpeed(float angular_speed);
  void AddAngularImpulse(const Vector& impulse);

  void UpdateBody(float delta_time, float damp = 0.0f);
  virtual void Draw(DemoHandler* handler) = 0;
};

}  // namespace student::archimedes

#endif