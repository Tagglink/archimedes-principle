#ifndef STUDENT_VERLET_BALL_H
#define STUDENT_VERLET_BALL_H

#include "verlet_particle.h"
#include "../SF_src/DemoHandler.h"

namespace student {

class VerletBall final : public VerletParticle
{
  Color color_;
  float radius_;
public:
  VerletBall(float radius);
  VerletBall(float radius, Color color);

  void SetColor(Color color) { color_ = color; }

  void Update(float delta_time) override;
  void Draw(DemoHandler* engine) const override;
};

} // namespace student

#endif