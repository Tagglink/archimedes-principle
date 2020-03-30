#include "verlet_particle.h"

namespace student {

VerletParticle::VerletParticle() :
  position_(0.0f),
  previous_position_(0.0f),
  force_(0.0f),
  mass_(1.0f),
  inverse_mass_(0.1f)
{

}

void VerletParticle::UpdatePosition(float delta_time, float damp)
{
  Vector new_position =
    (position_ * (2.0f - damp)) - 
    (previous_position_ * (1.0f - damp)) +
    (force_ * delta_time * delta_time * inverse_mass_);

  previous_position_ = position_;
  position_ = new_position;
}

void VerletParticle::AddForce(const Vector& delta_force)
{
  force_ += delta_force;
}

void VerletParticle::Move(const Vector& delta_position)
{
  position_ += delta_position;
}

void VerletParticle::SetPosition(const Point& new_position)
{
  previous_position_ = previous_position_ + new_position - position_;
  position_ = new_position;
}

Vector VerletParticle::GetVelocity(float delta_time) const
{
  return (position_ - previous_position_) / delta_time;
}

void VerletParticle::SetVelocity(const Vector& new_velocity, float delta_time)
{
  previous_position_ = position_ - (new_velocity * delta_time);
}

} // namespace student