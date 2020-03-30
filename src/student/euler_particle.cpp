#include "euler_particle.h"

#include "vector.h"

namespace student {

EulerParticle::EulerParticle() :
  EulerParticle(0.0f, 0.0f)
{

}

EulerParticle::EulerParticle(Point position) : 
  EulerParticle(position, 0.0f)
{

}

EulerParticle::EulerParticle(Point position, float mass) :
  position_(position),
  mass_(mass > 0.0f ? mass : 0.001f),
  velocity_(0.0f), 
  force_(0.0f), 
  inverse_mass_(1.0f / mass_)
{

}

void EulerParticle::UpdatePosition(float delta_time)
{
  Vector acceleration = force_ * inverse_mass_;
  velocity_ += acceleration * delta_time;
  position_ += velocity_ * delta_time;
}

void EulerParticle::AddForce(const Vector& force)
{
  force_ += force;
}

} // namespace student