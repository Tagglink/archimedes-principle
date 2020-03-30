#ifndef STUDENT_ARCHIMEDES_POINTMASS_H
#define STUDENT_ARCHIMEDES_POINTMASS_H

#include "student/vector.h"

namespace student::archimedes {

struct Pointmass final
{
  float mass;
  Point position;
  Pointmass(const float mass, const Point& position)
      : mass(mass)
      , position(position)
  {}
};

}  // namespace student::archimedes

#endif
