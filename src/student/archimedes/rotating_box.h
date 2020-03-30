#ifndef ROTATING_BOX_H
#define ROTATING_BOX_H

#include <array>

#include "student/vector.h"
#include "SF_src/DemoHandler.h"

namespace student::archimedes {

class RotatingBox final
{
  float orientation_;
  float angular_momentum_;
  float torque_;
  float moment_of_inertia_;
  float inverted_moment_of_inertia_;

  Point position_;
  float width_;
  float height_;

  // top right, bottom right, bottom left, top left
  std::array<Point, 4> local_corners_;
public:
  RotatingBox(const Point& position, float mass, float width, float height);

  auto RotateLocalVector(const Vector& vector_to_rotate) -> Vector;
  auto RotateGlobalVector(const Vector& vector_to_rotate) -> Vector;
  auto LocalToGlobal(const Point& local_point) -> Point;
  auto GlobalToLocal(const Point& global_point) -> Point;

  void ClearForces();
  void AddForce(const Vector& force, const Point& global_point);
  auto GetVelocityAtPoint(const Point& global_point) -> Vector;
  auto GetAngularVelocity() -> float;
  void AddAngularImpulse(float angular_impulse);

  void Update(float delta_time, float damp = 0.0f);
  void Draw(DemoHandler* handler);

  auto Overlaps(const Point& global_point) -> bool;
};

}  // namespace student::archimedes

#endif