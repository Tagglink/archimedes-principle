#ifndef STUDENT_SIMULATION_H
#define STUDENT_SIMULATION_H

#include <array>
#include <string>
#include <vector>

#include "SF_src/Demo.h"
#include "student/archimedes/liquid_body_2d.h"
#include "student/archimedes/pointmass_body_2d.h"
#include "student/plane.h"
#include "student/vector.h"

namespace student::archimedes {

class Simulation final : public Demo
{
public:
  Simulation();

  virtual void update(DemoHandler*);

  virtual auto getName() -> const std::string;
  virtual auto getInfo() -> const std::string;

private:
  float time_step_;
  float damping_;
  float user_force_;

  std::vector<std::shared_ptr<PointmassBody2D>> bodies_;
  std::vector<std::shared_ptr<LiquidBody2D>> liquids_;
  float gravity_acceleration_;

  void InitializeSimulation();
  void ResetSimulation();

  void SimulateLiquid(const std::shared_ptr<LiquidBody2D>& liquid);

  void HandleSlicing(const Point& point_a, const Point& point_b);
  void HandlePushing(const Point& point_a, const Point& point_b);

  auto SliceBody(const std::shared_ptr<PointmassBody2D>& body_to_slice,
                 const Plane& slicing_plane)
      -> std::array<std::shared_ptr<PointmassBody2D>, 2>;

  auto GetSlicingData(Point slice_a, Point slice_b) -> std::array<Plane, 3>;
};

}  // namespace student::archimedes

#endif