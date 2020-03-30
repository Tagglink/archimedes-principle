#ifndef STUDENT_ARCHIMEDES_POINTMASS_BODY_2D_H
#define STUDENT_ARCHIMEDES_POINTMASS_BODY_2D_H

#include <memory>
#include <vector>

#include "SF_src/DemoHandler.h"
#include "student/archimedes/pointmass.h"
#include "student/archimedes/rigidbody_2d.h"
#include "student/archimedes/triangle.h"

namespace student::archimedes {

// A pointmass body in 2D. Simulates rotational force
// but not collision. Must be convex.
class PointmassBody2D : public Rigidbody2D
{
public:
  PointmassBody2D(const std::vector<Pointmass>& pointmasses,
                  const Color color = Color::RED);
  PointmassBody2D(const std::vector<Point>& points,
                  const float density,
                  const Color color = Color::RED);

  void Update(float delta_time, float damp = 0.0f);
  void Draw(DemoHandler* handler) override;
  auto GetShape() -> std::vector<Point>;
  auto GetTotalArea() -> float;
  auto GetDensity() -> float;
  auto GetColor() -> Color;

private:
  std::vector<std::shared_ptr<Pointmass>> pointmasses_;
  std::vector<Triangle> faces_;
  Color color_;
  float density_;

  void InitializeBody(const std::vector<Pointmass>& pointmasses);
  auto Triangulate(int points_length) -> std::vector<Triangle>;
  void DrawTriangle(DemoHandler* handler, Triangle triangle);
};

}  // namespace student::archimedes

#endif