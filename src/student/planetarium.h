#ifndef STUDENT_PLANETARIUM_H
#define STUDENT_PLANETARIUM_H

#include <string>
#include <vector>

#include "../SF_src/Demo.h"
#include "../SF_src/DemoHandler.h"
#include "verlet_ball.h"
#include "vector.h"

namespace student {

class Planetarium final : public Demo {
  float time_step_;
  bool simulate_gravity_;

  std::vector<VerletBall*> planets_;

  float gravitational_constant_;

  float earth_mass_;
  float moon_mass_;

  float moon_earth_distance_;
  float earth_radius_;
  float moon_radius_;

  float moon_speed_;

  int new_moon_scale_;
  Point earth_starting_position_;
  float moon_density_;

  Point mouse_clicked_position_;
  bool is_drawing_line_;

  void InitializeSimulation();
  void Reset();
  void ToggleGravity();
  void AddNewMoon(int scale, 
    Point starting_position, Vector starting_velocity);
  void DrawUI(DemoHandler* engine);
public:
  Planetarium();
  virtual ~Planetarium();

  void SimulateGravity();
  void AddPlanet(float radius, float mass, float delta_time,
    Point startingPos, Vector startingVelocity, Color color);

  void update(DemoHandler* engine) override;
  const std::string getName() override;
  const std::string getInfo() override;
};


} // namespace student

#endif
