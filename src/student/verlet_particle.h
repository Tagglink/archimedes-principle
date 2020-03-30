#ifndef STUDENT_VERLET_PARTICLE_H
#define STUDENT_VERLET_PARTICLE_H

#include "entity.h"
#include "vector.h"

namespace student
{

class VerletParticle : public Entity
{
  Point position_;
  Point previous_position_;
  Vector force_;
  float mass_;
  float inverse_mass_;
public:
  VerletParticle();

  virtual void Update(float delta_time) = 0;
  virtual void Draw(DemoHandler* engine) const = 0;

  void UpdatePosition(float delta_time, float damp = 0.0f);
  void AddForce(const Vector& delta_force);
  void Move(const Vector& delta_position);

  Point GetPosition() const { return position_; }
  void SetPosition(const Point& new_position);
  Vector GetVelocity(float delta_time) const;
  void SetVelocity(const Vector& new_velocity, float delta_time);
  float GetMass() const { return mass_; }
  float GetInverseMass() const { return inverse_mass_; }
  void SetMass(float new_mass) { mass_ = new_mass; inverse_mass_ = 1.0f / new_mass; }
  Vector GetForce() const { return force_; }
  void SetForce(const Vector& new_force) { force_ = new_force; }
};

} // namespace student

#endif