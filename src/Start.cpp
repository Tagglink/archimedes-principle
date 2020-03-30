#include "SF_src/OpenGLStuff.h"
#include "SF_src/DemoHandler.h"

#include "student/ball_cannon.h"
#include "student/spring_bodies.h"
#include "student/planetarium.h"
#include "student/archimedes/rotating_boxes.h"
#include "student/archimedes/simulation.h"

/*
 The entry point for the program.
 You need to add your demos before you call start.
 */
int main(int argc, char* argv[])
{
  DemoHandler::inst().addDemo(new student::BallCannon());
  DemoHandler::inst().addDemo(new student::SpringBodies());
  DemoHandler::inst().addDemo(new student::Planetarium());
  DemoHandler::inst().addDemo(new student::archimedes::RotatingBoxes());
  DemoHandler::inst().addDemo(new student::archimedes::Simulation());

  start(argc, argv);//function in "OpenGLStuff"

  return 0;
};

/*
 (c)2014 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */