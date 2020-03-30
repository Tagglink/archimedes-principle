#ifndef STUDENT_ENTITY_H
#define STUDENT_ENTITY_H

#include "../SF_src/DemoHandler.h"
#include "vector.h"

namespace student {

// A drawable object to be updated with physics
class Entity  {
public:
  virtual void Update(float delta_time) = 0;
  virtual void Draw(DemoHandler* engine) const = 0;
};

} // namespace student

#endif