#include "student/archimedes/slicer.h"

#include <array>
#include <vector>

#include "student/plane.h"
#include "student/vector.h"

namespace {

const float plane_thickness = 0.0000001f;

inline auto InFront(float d) -> bool
{
  return d > plane_thickness;
}

inline auto Behind(float d) -> bool
{
  return d < -plane_thickness;
}

inline auto On(float d) -> bool
{
  return d <= plane_thickness && d >= -plane_thickness;
}

template <typename T>
auto Contains(const std::vector<T>& elements, const T& value) -> bool
{
  for (T element : elements) {
    if (element == value) {
      return true;
    }
  }

  return false;
}

}  // namespace

namespace student::archimedes::slicer {

// Implementation of the Sutherland-Hodgman polygon clipping
// algorithm, adapted to return polygons on both sides of the plane.
// see
// https://gamedevelopment.tutsplus.com/tutorials/how-to-dynamically-slice-a-convex-shape--gamedev-14479
auto SlicePolygon(const std::vector<Point>& polygon, const Plane& slicing_plane)
    -> std::array<std::vector<Point>, 2>
{
  std::vector<Point> front_polygon;
  std::vector<Point> back_polygon;

  Point point_a = polygon.back();
  float point_a_distance = slicing_plane.Distance(point_a);

  for (int i = 0; i < polygon.size(); i++) {
    Point point_b = polygon.at(i);
    float point_b_distance = slicing_plane.Distance(point_b);

    if (::InFront(point_b_distance)) {
      if (::Behind(point_a_distance)) {
        Point intersection =
            Intersection(point_b, point_a, point_b_distance, point_a_distance);
        front_polygon.push_back(intersection);
        back_polygon.push_back(intersection);
      }

      front_polygon.push_back(point_b);
    } else if (::Behind(point_b_distance)) {
      if (::InFront(point_a_distance)) {
        Point intersection =
            Intersection(point_a, point_b, point_a_distance, point_b_distance);
        front_polygon.push_back(intersection);
        back_polygon.push_back(intersection);
      } else if (::On(point_a_distance)) {
        back_polygon.push_back(point_a);
      }

      back_polygon.push_back(point_b);
    } else {
      front_polygon.push_back(point_b);

      if (::On(point_a_distance)) {
        back_polygon.push_back(point_b);
      }
    }

    point_a = point_b;
    point_a_distance = point_b_distance;
  }

  return {front_polygon, back_polygon};
}

auto Intersection(const Point& point_a,
                  const Point& point_b,
                  const float point_a_distance,
                  const float point_b_distance) -> Point
{
  Vector line = point_b - point_a;

  float interpolant =
      std::abs(point_a_distance)
      / (std::abs(point_a_distance) + std::abs(point_b_distance));

  Point intersection = (line * interpolant) + point_a;

  return intersection;
}

// see if a polygon intersects a plane
auto Intersects(const Plane& plane, const std::vector<Point>& polygon) -> bool
{
  // check the sign of the distance of the first point
  bool first_sign = std::signbit(plane.Distance(polygon.at(0)));

  for (int i = 1; i < polygon.size(); i++) {
    bool current_sign = std::signbit(plane.Distance(polygon.at(i)));
    // compare with the sign of the distance for all other points. if there is
    // ever a difference, the polygon intersects.
    if (first_sign != current_sign) {
      return true;
    }
  }

  return false;
}

auto IsStrictlyWithinBounds(const Plane& bounding_plane_a,
                            const Plane& bounding_plane_b,
                            const std::vector<Point>& polygon) -> bool
{
  for (int i = 0; i < polygon.size(); i++) {
    float distance_a = bounding_plane_a.Distance(polygon.at(i));
    float distance_b = bounding_plane_b.Distance(polygon.at(i));

    if (::Behind(distance_a) || ::Behind(distance_b)) {
      return false;
    }
  }
  return true;
}

auto IsWithinBounds(const Plane& bounding_plane_a,
                    const Plane& bounding_plane_b,
                    const std::vector<Point>& polygon) -> bool
{
  for (int i = 0; i < polygon.size(); i++) {
    float distance_a = bounding_plane_a.Distance(polygon.at(i));
    float distance_b = bounding_plane_b.Distance(polygon.at(i));

    if (::InFront(distance_a) && ::InFront(distance_b)) {
      return true;
    }
  }
  return false;
}

}  // namespace student::archimedes::slicer