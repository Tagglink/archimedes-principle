#ifndef STUDENT_ARCHIMEDES_PLANE_H
#define STUDENT_ARCHIMEDES_PLANE_H

#include "student/vector.h"
#include "SF_src/DemoHandler.h"

namespace student {

struct Plane final
{
  Point point_in_plane;
  Vector normal;

  Plane(Point point_in_plane, Vector normal)
      : point_in_plane(point_in_plane)
      , normal(normal)
  {}

  auto Distance(Point point) const -> float
  {
    return (point - point_in_plane).Dot(normal);
  }

  void Draw(DemoHandler* handler, Color color)
  {
    Vector normal_of_normal = Vector(-normal.y, normal.x, 0.0f);
    handler->drawLine(point_in_plane + (normal_of_normal * 1000.0f),
                      point_in_plane + (normal_of_normal * -1000.0f),
                      color,
                      0.01f);
  }
};

}  // namespace student::archimedes

#endif