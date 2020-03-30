#ifndef STUDENT_ARCHIMEDES_TRIANGLE_H
#define STUDENT_ARCHIMEDES_TRIANGLE_H

#include "SF_src/DemoHandler.h"

namespace student::archimedes {

struct Triangle final
{
  int a;
  int b;
  int c;
  Color color;

  Triangle(int a, int b, int c)
      : Triangle(a, b, c, Color::WHITE)
  {}

  Triangle(int a, int b, int c, Color color)
      : a(a)
      , b(b)
      , c(c)
      , color(color)
  {}
};

}  // namespace student::archimedes

#endif