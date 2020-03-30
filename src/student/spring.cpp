#include "spring.h"

#include <iostream>

namespace student {

Spring::Spring(float stiffness, EulerParticle* body1, EulerParticle* body2, 
  float resting_length) :
  stiffness_(stiffness), body1_(body1), body2_(body2), 
  resting_length_(resting_length)
{

}

Spring::~Spring()
{

}

void Spring::SetStiffness(float value)
{
  stiffness_ = value;
}

void Spring::Update(float delta_time)
{
  const Vector d = body2_->GetPosition() - body1_->GetPosition();
  const float d_magnitude = d.Magnitude();
  const Vector d_normalized = d / d_magnitude;
  const Vector force = d_normalized * stiffness_ * (d_magnitude - resting_length_);

  body1_->AddForce(force);
  body2_->AddForce(-force);
}

void Spring::Draw(DemoHandler* engine) const
{
  engine->drawLine(
    body1_->GetPosition(), 
    body2_->GetPosition(), 
    Color::PINK
  );
}

} // namespace student