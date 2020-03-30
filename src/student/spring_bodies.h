#ifndef STUDENT_SPRING_BODIES_H
#define STUDENT_SPRING_BODIES_H

#include <string>
#include <vector>

#include "../SF_src/Demo.h"
#include "euler_ball.h"
#include "spring.h"

namespace student {

class SpringBodies final : public Demo {
  std::vector<EulerBall*> balls_;
  std::vector<Spring*> springs_;

  float delta_time_;
  Vector gravity_;

  void Reset();
public:
  SpringBodies();
  virtual ~SpringBodies();

  void update(DemoHandler* engine) override;
  const std::string getName() override;
  const std::string getInfo() override;
};


} // namespace student

#endif
