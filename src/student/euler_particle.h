#ifndef STUDENT_BODY_H
#define STUDENT_BODY_H

#include "entity.h"

namespace student {

class EulerParticle : public Entity {
  Point position_;
  Vector velocity_;
  Vector force_;
  float mass_;
  float inverse_mass_;
public:
  EulerParticle();
  EulerParticle(Point position);
  EulerParticle(Point position, float mass);

  virtual void Update(float delta_time) = 0;
  virtual void Draw(DemoHandler* engine) const = 0;

  void UpdatePosition(float delta_time);
  void AddForce(const Vector& force);

  Point GetPosition() const { return position_; }
  void SetPosition(Point position) noexcept { position_ = position; }
  Vector GetVelocity() const { return velocity_; }
  void SetVelocity(Vector velocity) noexcept { velocity_ = velocity; }
  float GetMass() const noexcept { return mass_; }
  void SetMass(float mass) noexcept { mass_ = mass; inverse_mass_ = 1.0f / mass_; }
  Vector GetForce() const { return force_; }
  void SetForce(Vector force) noexcept { force_ = force; }
  float GetInverseMass() const noexcept { return inverse_mass_; }
};

} // namespace student

#endif // !STUDENT_BODY_H
