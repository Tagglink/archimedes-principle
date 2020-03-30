#ifndef STUDENT_SPRING_H
#define STUDENT_SPRING_H

#include "../SF_src/DemoHandler.h"
#include "euler_particle.h"
#include "entity.h"

namespace student {

class Spring final : public Entity {
  EulerParticle* body1_;
  EulerParticle* body2_;
  float stiffness_;
  float resting_length_;
public:
  Spring(float stiffness, EulerParticle* body1, EulerParticle* body2,
    float resting_length = 1.0f);
  virtual ~Spring();

  void SetStiffness(float value);

  void Update(float delta_time) override;
  void Draw(DemoHandler* engine) const override;
};

} // namespace student

#endif