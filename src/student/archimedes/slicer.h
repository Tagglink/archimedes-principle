#ifndef STUDENT_ARCHIMEDES_SLICER_H
#define STUDENT_ARCHIMEDES_SLICER_H

#include <array>
#include <memory>
#include <vector>

#include "student/archimedes/pointmass_body_2d.h"
#include "student/plane.h"
#include "student/vector.h"

namespace student::archimedes::slicer {

extern auto SlicePolygon(const std::vector<Point>& polygon,
                         const Plane& slicing_plane)
    -> std::array<std::vector<Point>, 2>;

extern auto Intersection(const Point& point_a,
                         const Point& point_b,
                         const float point_a_distance,
                         const float point_b_distance) -> Point;

extern auto Intersects(const Plane& plane, const std::vector<Point>& polygon)
    -> bool;

// Returns true if a polygon has all points between the two planes
extern auto IsStrictlyWithinBounds(const Plane& bounding_plane_a,
                                   const Plane& bounding_plane_b,
                                   const std::vector<Point>& polygon) -> bool;

// Returns true if a polygon has at least one point between the two planes
extern auto IsWithinBounds(const Plane& bounding_plane_a,
                           const Plane& bounding_plane_b,
                           const std::vector<Point>& polygon) -> bool;

}  // namespace student::archimedes::slicer

#endif