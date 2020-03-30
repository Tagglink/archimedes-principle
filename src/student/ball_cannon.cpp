#include "ball_cannon.h"

#include <string>

#include "../SF_src/DemoHandler.h"
#include "vector.h"

namespace student {

// I initialize all of the values here.
// they are named appropriately.
BallCannon::BallCannon() :
  // assume 60 updates per second
  time_interval_(1.0f / 60.0f),

  cannon_pos_(0, 0, 0), target_(),

  // spawn the ball somewhere far away with zero velocity
  ball_pos_(100, 0, 0), ball_velocity_(0, 0, 0), 
  ball_speed_(1.0f), ball_radius_(0.3f),
  ball_grounded_(true),

  // these values look good
  bounciness_(0.5f), friction_(0.5f),

  // REAL (meters per square second) values for graviation. WOW!
  gravity_acceleration_(0, -9.82f, 0)
{

}


BallCannon::~BallCannon()
{

}

// sets the ball position to the cannon position
// and applies a velocity to the ball in the direction of target 
void BallCannon::ShootBall()
{
  // set the ball position to the cannon position
  ball_pos_ = cannon_pos_;

  // end point minus start point gives a directional vector
  ball_velocity_ = (target_ - cannon_pos_) * ball_speed_;
}

void BallCannon::update(DemoHandler* engine)
{
  // user input
  // update the target to shoot towards
  target_ = engine->getMouseLocation();

  if (engine->isMouseDown(Button::LEFT)) {
    ShootBall();
  }
  if (engine->keyTyped('w') && cannon_pos_.y < 10.0f) {
    cannon_pos_.y += 1.0f;
  }
  if (engine->keyTyped('s') && cannon_pos_.y > 0.0f) {
    cannon_pos_.y -= 1.0f;
  }
  
  // draw the graphics
  engine->drawText(target_, "shoot ball here (Left Mouse)");
  engine->drawText(cannon_pos_ + Point(0, -0.2f, 0), "'W' = move up");
  engine->drawText(cannon_pos_ + Point(0, -0.5f, 0), "'S' = move down");
  engine->drawLine(cannon_pos_, target_, Color::CYAN, 0.01f);
  engine->drawPoint(ball_pos_, Color::GREEN, ball_radius_);

  // physics

  // if we apply gravity when the ball is already grounded,
  // it will fall through the ground when it has stopped bouncing
  if (!ball_grounded_) {
    // apply downwards acceleration
    ball_velocity_ += gravity_acceleration_ * time_interval_;
  }

  // apply ball velocity
  ball_pos_ += ball_velocity_ * time_interval_;

  // handle "collision"

  // if the ball is "grounded" but is not actually touching the ground,
  if (ball_grounded_ && ball_pos_.y - ball_radius_ > 0.0f) {
    ball_grounded_ = false;
  }
  // if the ball is "not grounded" and is actually touching the ground,
  else if (!ball_grounded_ && ball_pos_.y - ball_radius_ < 0.0f) {
    ball_grounded_ = true;

    // bounce the ball
    ball_velocity_.y = -ball_velocity_.y * bounciness_;

    // apply friction in x and z axes
    ball_velocity_.x *= friction_;
    ball_velocity_.z *= friction_;
  }
}

const std::string BallCannon::getName()
{
  return "Ball Cannon (student version)";
}

const std::string BallCannon::getInfo()
{
  return " \nShoots out a ball from a cannon with variable direction.\n";
}

} // namespace student