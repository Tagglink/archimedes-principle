#ifndef STUDENT_BALL_CANNON_H
#define STUDENT_BALL_CANNON_H

#include "../SF_src/Demo.h"

#include "../SF_src/Point.h"
#include "vector.h"

namespace student {

// this is a quick and dirty solution with only a single ball
// and assuming an infinite plane y = 0 with normal (0, 1, 0)
class BallCannon final : public Demo
{
  float time_interval_;

  Point cannon_pos_;
  Point target_;

  Point ball_pos_;
  Vector ball_velocity_;
  float ball_speed_;
  float ball_radius_;
  bool ball_grounded_;

  // should be a number below 1.
  // you probably understand what happens otherwise.
  float bounciness_;

  // acceleration along the x and z axes
  // only on the frame of becoming grounded
  float friction_;

  Vector gravity_acceleration_;

  void ShootBall();
public:
  BallCannon();
  virtual ~BallCannon();

  void update(DemoHandler*) override;
  const std::string getName() override;
  const std::string getInfo() override;
};

} // namespace student  

#endif // !STUDENT_BALL_CANNON_H
