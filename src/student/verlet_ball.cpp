#include "verlet_ball.h"

namespace student {

VerletBall::VerletBall(float radius) :
  radius_(radius), color_(Color::GREEN)
{

}

VerletBall::VerletBall(float radius, Color color) :
  radius_(radius), color_(color)
{

}

void VerletBall::Update(float delta_time)
{
  UpdatePosition(delta_time, 0.0f);
}

void VerletBall::Draw(DemoHandler* engine) const
{
  engine->drawPoint(GetPosition(), color_, radius_);
}

} // namespace student