#ifndef STUDENT_BALL_H
#define STUDENT_BALL_H

#include "../SF_src/DemoHandler.h"
#include "euler_particle.h"
#include "vector.h"

namespace student {

class EulerBall final : public EulerParticle {
  Color color_;
  float radius_;
public:
  EulerBall(float radius);
  EulerBall(float radius, Point position);

  bool Overlaps(Point point) const;

  void SetColor(Color color) { color_ = color; }

  void Update(float delta_time) override;
  void Draw(DemoHandler* engine) const override;
};

} // namespace student

#endif