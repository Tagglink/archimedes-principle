#ifndef STUDENT_ROTATING_BOXES_H
#define STUDENT_ROTATING_BOXES_H

#include <array>

#include "SF_src/Demo.h"
#include "student/vector.h"
#include "rotating_box.h"

namespace student::archimedes {

class RotatingBoxes final : public Demo
{
  float time_step_;

  RotatingBox box_a_;
  RotatingBox box_b_;
  std::array<Point, 2> local_points_a_;
  std::array<Point, 2> local_points_b_;

public:
  RotatingBoxes();

  virtual void update(DemoHandler*);

  virtual auto getName() -> const std::string;
  virtual auto getInfo() -> const std::string;
};

}  // namespace student::archimedes

#endif