#include "geometry.h"

#include "vector.h"
#include "plane.h"

namespace student::geometry {

auto AreaOfTriangleXY(Point a, Point b, Point c) -> float
{
  // area of triangle: base * height * 0.5
  // the base is (b - a).magnitude
  // the height can be gotten by treating the base as a plane and getting the
  // distance between point c and the plane
  Vector base = b - a;

  float base_magnitude = base.Magnitude();

  Vector ab_normal = Vector(-base.y, base.x, 0.0f) / base_magnitude;

  float height = std::abs((c - a).Dot(ab_normal));

  return base_magnitude * height * 0.5f;
}

auto AreaOfConvexPolygonXY(const std::vector<Point>& shape) -> float
{
  // treat the polygon as triangulated by a triangle fan

  float total_area = 0.0f;

  for (int i = 0; i < shape.size() - 2; i++) {
    Point a = shape.at(0);
    Point b = shape.at(i + 1);
    Point c = shape.at(i + 2);

    total_area += AreaOfTriangleXY(a, b, c);
  }

  return total_area;
}

auto PointOverlapsConvexPolygonXY(const Point& point,
                                  const std::vector<Point>& shape) -> bool
{
  auto bounding_planes = GetPlaneBounds(shape);
  for (int i = 0; i < bounding_planes.size(); i++) {
    if (bounding_planes.at(i).Distance(point) < 0.0f) {
      return false;
    }
  }

  return true;
}

auto GetPlaneBounds(const std::vector<Point>& shape) -> std::vector<Plane>
{
  std::vector<Plane> planes;

  Point point_a = shape.back();

  for (int i = 0; i < shape.size(); i++) {
    Point point_b = shape.at(i);

    planes.push_back(DefinePlane(point_a, point_b));

    point_a = point_b;
  }

  return planes;
}

auto DefinePlane(const Point& point_a, const Point& point_b) -> Plane
{
  Vector line = point_b - point_a;

  Vector plane_normal = Vector(-line.y, line.x, 0.0f).Normalized();

  return Plane(point_a, plane_normal);
}

}  // namespace student::geometry