#include "planetarium.h"

#include "../SF_src/DemoHandler.h"

namespace student {

Planetarium::Planetarium() :
  time_step_(1.0f / 60.0f),
  simulate_gravity_(true),
  planets_(),
  // I've scaled the real-life constants below so that the following is true:
  // Real-life seconds are divided by the number of seconds in a day
  // (s / 86400)
  // Real-life kilograms are divided by the mass of the moon in kilograms
  // (kg / (7.35 * 10^22))
  // Real-life meters are divided by the diameter of the earth in meters times 5
  // (m / (6.371 * 10^7))
  gravitational_constant_(0.14152f),

  earth_mass_(81.2245f),
  moon_mass_(1.0f),

  moon_earth_distance_(6.03359f),
  earth_radius_(0.09889f),
  moon_radius_(0.02669f),

  moon_speed_(1.3897f),

  new_moon_scale_(1),
  earth_starting_position_(5.0f, 5.0f, 0.0f),
  // density = mass / volume
  moon_density_(moon_mass_ / ((4.0f * 3.1415 *
    moon_radius_ * moon_radius_ * moon_radius_) / 3.0f)),

  mouse_clicked_position_(0.0f),
  is_drawing_line_(false)
{
  InitializeSimulation();
}

void Planetarium::update(DemoHandler* engine)
{
  if (simulate_gravity_) {
    SimulateGravity();
  }

  for (auto planet : planets_) {
    planet->Update(time_step_);
    planet->SetForce(0.0f);
    planet->Draw(engine);
  }

  if (engine->keyTyped('r')) {
    Reset();
  }
  if (engine->keyTyped('g')) {
    ToggleGravity();
  }
  for (int i = 0; i < 9; i++) {
    if (engine->keyTyped('1' + i)) {
      new_moon_scale_ = i + 1;
    }
  }

  if (engine->isMouseDown(Button::LEFT) && !is_drawing_line_) {
    mouse_clicked_position_ = engine->getMouseLocation();

    is_drawing_line_ = true;
  }
  else if (!engine->isMouseDown(Button::LEFT) && is_drawing_line_) {
    AddNewMoon(new_moon_scale_, mouse_clicked_position_,
      Point(engine->getMouseLocation()) - mouse_clicked_position_
    );
    is_drawing_line_ = false;
  }

  DrawUI(engine);
}

void Planetarium::InitializeSimulation()
{
  // The earth
  AddPlanet(earth_radius_, earth_mass_, time_step_,
    earth_starting_position_,
    { 0.0f, 0.0f, 0.0f },
    Color::BLUE
  );

  // The moon
  AddPlanet(moon_radius_, moon_mass_, time_step_,
    // The speed of the moon is perpendicular to earth since
    // it starts translated along the x-axis with a velocity along the y-axis
    earth_starting_position_ + Point(moon_earth_distance_, 0.0f, 0.0f),
    { 0.0f, moon_speed_, 0.0f },
    Color::GRAY
  );

  // reset user input as well (because that was my intuition when testing)
  new_moon_scale_ = 1;
  simulate_gravity_ = true;
}

void Planetarium::SimulateGravity()
{
  Vector direction_of_gravity;
  float square_distance = 0.0f;
  float strength = 0.0f;

  for (auto planet_a : planets_) {
    for (auto planet_b : planets_) {
      if (planet_a != planet_b) {
        direction_of_gravity =
          planet_b->GetPosition() - planet_a->GetPosition();

        square_distance = direction_of_gravity.SquareMagnitude();

        direction_of_gravity = direction_of_gravity.Normalized();

        strength = (gravitational_constant_ * 
          planet_a->GetMass() * planet_b->GetMass()) /
          square_distance;

        planet_a->AddForce(direction_of_gravity * strength);
      }
    }
  }
}

void Planetarium::AddPlanet(float radius, float mass, float delta_time,
  Point startingPos, Vector startingVelocity, Color color)
{
  VerletBall* planet = new VerletBall(radius);
  planet->SetPosition(startingPos);
  planet->SetVelocity(startingVelocity, delta_time);
  planet->SetMass(mass);
  planet->SetColor(color);

  planets_.push_back(planet);
}

void Planetarium::AddNewMoon(int scale, 
  Point starting_position, 
  Vector starting_velocity)
{
  // scale the diameter
  float new_radius = moon_radius_ * scale;
  // mass = density * volume
  float new_mass = (moon_density_ * 4.0f * 3.1415f
    * new_radius * new_radius * new_radius) / 3.0f;

  AddPlanet(new_radius, new_mass, time_step_,
    starting_position,
    starting_velocity, 
    Color::GRAY
  );
}

void Planetarium::DrawUI(DemoHandler* engine)
{
  if (is_drawing_line_) {
    engine->drawLine(mouse_clicked_position_, engine->getMouseLocation(),
      Color::CYAN, 0.01f);
  }

  engine->drawText({ 10.0f, 2.0f, 0.0f }, "G: Toggle gravity.");
  engine->drawText({ 10.0f, 1.5f, 0.0f }, "R: Reset simulation.");
  engine->drawText({ 10.0f, 1.0f, 0.0f }, "Drag left mouse: Add new moon.");
  engine->drawText({ 10.0f, 0.5f, 0.0f }, "1-9: Adjust scale "
    "(and mass) of new moons.\n");
}

const std::string Planetarium::getName()
{
  return "The moon's orbit around the earth";
}

const std::string Planetarium::getInfo()
{
  return "Press F10 to make the grid go away.\n\n"
    "Seconds are divided by the number of seconds in a day.\n"
    "Kilograms are divided by the mass of the moon in kilograms.\n"
    "Meters are divided by the diameter of the earth in meters times 5.\n\n";
}

Planetarium::~Planetarium()
{
  for (auto planet : planets_) {
    delete planet;
  }
}

void Planetarium::Reset()
{
  for (auto planet : planets_) {
    delete planet;
  }
  planets_.clear();

  InitializeSimulation();
}

void Planetarium::ToggleGravity()
{
  simulate_gravity_ = !simulate_gravity_;
}

} // namespace student
