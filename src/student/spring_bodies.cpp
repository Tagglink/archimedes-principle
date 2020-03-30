#include "spring_bodies.h"

#include "euler_ball.h"
#include "spring.h"

#include <iostream>

namespace student {

void SpringBodies::Reset()
{
  balls_.at(0)->SetPosition({ 2.0f, 2.0f, 0.0f });
  balls_.at(1)->SetPosition({ 3.0f, 4.0f, 0.0f });
  balls_.at(2)->SetPosition({ 4.0f, 2.0f, 0.0f });

  for (auto ball : balls_) {
    ball->SetVelocity(0.0f);
  }
}

SpringBodies::SpringBodies() :
  delta_time_(1.0f / 60.0f),
  gravity_(Vector(0.0f, -9.82f, 0.0f)),

  balls_({
    new EulerBall(0.4f, Point(2.0f, 2.0f, 0.0f)),
    new EulerBall(0.4f, Point(4.0f, 2.0f, 0.0f)),
    new EulerBall(0.4f, Point(3.0f, 4.0f, 0.0f))
    }),
  springs_({
    new Spring(2.0f, balls_[0], balls_[1], 1.0f),
    new Spring(2.0f, balls_[0], balls_[2], 1.0f),
    new Spring(2.0f, balls_[1], balls_[2], 1.0f)
    })
{

}

SpringBodies::~SpringBodies()
{
  for (auto spring : springs_) {
    delete spring;
  }
  for (auto ball : balls_) {
    delete ball;
  }
}

void SpringBodies::update(DemoHandler* engine)
{
  for (auto spring : springs_) {
    spring->Update(delta_time_);
  }

  for (auto ball : balls_) {
    //ball->AddForce(gravity_ * ball->GetMass());
    ball->Update(delta_time_);
  }

  Vector mousePosition = engine->getMouseLocation();

  if (engine->keyTyped('1')) {
    for (auto spring : springs_) {
      spring->SetStiffness(2.0f);
    }
  }
  else if (engine->keyTyped('2')) {
    for (auto spring : springs_) {
      spring->SetStiffness(6.0f);
    }
  }

  // apply user input after updating physics, so that we hard-set the position
  // of the ball
  if (engine->keyTyped('r')) {
    Reset();
  }

  if (engine->isMouseDown(LEFT)) {
    balls_.at(0)->SetPosition(mousePosition);
  }

  for (auto spring : springs_) {
    spring->Draw(engine);
  }

  for (auto ball : balls_) {
    ball->Draw(engine);
  }
}

const std::string SpringBodies::getName()
{
  return "Springs connected with masses";
}

const std::string SpringBodies::getInfo()
{
  return "Hold left mouse to move one of the spheres.\n " 
    "R: reset, 1-2: different stiffness";
}

} // namespace student
