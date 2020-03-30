#ifndef STUDENT_ARCHIMEDES_LIQUID_BODY_2D_H
#define STUDENT_ARCHIMEDES_LIQUID_BODY_2D_H

#include "SF_src/DemoHandler.h"
#include "student/archimedes/pointmass_body_2d.h"
#include "student/plane.h"
#include "student/vector.h"

namespace student::archimedes {

class LiquidBody2D
{
  float width_;
  float height_;
  float height_extension_;
  float density_;
  Point position_;
  Vector surface_normal_;

public:
  LiquidBody2D(float width, float height, Point position, float density);

  void HandleBodies(const std::vector<std::shared_ptr<PointmassBody2D>>& bodies,
                    const float gravity_acceleration);

  void Draw(DemoHandler* handler);

  // Returns an array with the liquid's left bounding plane as the first
  // element, and the right bounding plane as the second element.
  auto GetHorisontalBounds() -> std::array<Plane, 2>;
  // Returnas an array with the liquid's top bounding plane as the first
  // element, and the right bounding plane as the second element.
  auto GetVerticalBounds() -> std::array<Plane, 2>;

  void SetDensity(const float density) { density_ = density; }
  auto GetDensity() -> float { return density_; }
};
}  // namespace student::archimedes

#endif