#include "euler_ball.h"

#include "vector.h"
#include "../SF_src/DemoHandler.h"

namespace student {

EulerBall::EulerBall(float radius) :
  EulerBall(radius, 0.0f)
{

}

EulerBall::EulerBall(float radius, Point position) :
  radius_(radius), color_(Color::GREEN), 
  EulerParticle(position, radius * radius * 3.14f)
{

}

bool EulerBall::Overlaps(Point point) const
{
  Vector distance = GetPosition() - point;

  if (distance.SquareMagnitude() < radius_ * radius_) {
    return true;
  }
  else {
    return false;
  }
}

void EulerBall::Update(float delta_time)
{
  UpdatePosition(delta_time);
  SetForce(0.0f);
}

void EulerBall::Draw(DemoHandler* engine) const
{
  engine->drawPoint(GetPosition(), color_, radius_);
}

} // namespace student