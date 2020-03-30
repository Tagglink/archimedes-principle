#ifndef STUDENT_GEOMETRY_H
#define STUDENT_GEOMETRY_H

#include <vector>

#include "plane.h"
#include "vector.h"

namespace student::geometry {

extern auto AreaOfTriangleXY(Point a, Point b, Point c) -> float;

extern auto AreaOfConvexPolygonXY(const std::vector<Point>& shape) -> float;

// assuming that the polygon is defined in counter-clockwise order, checks to
// see if a point is within the bounds of a polygon
extern auto PointOverlapsConvexPolygonXY(const Point& point,
                                         const std::vector<Point>& shape)
    -> bool;

// gets the plane bounds with normals directed inwards if the polygon is defined
// in counter-clockwise order, or outwards if in clockwise order.
extern auto GetPlaneBounds(const std::vector<Point>& shape)
    -> std::vector<Plane>;

// gets a plane defined by two points with point a as the anchor point, and with
// the normal pointing upwards if point a is left of point b
extern auto DefinePlane(const Point& point_a, const Point& point_b) -> Plane;

}  // namespace student::geometry

#endif