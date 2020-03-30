#ifndef STUDENT_VECTOR_H
#define STUDENT_VECTOR_H

#include <cmath>

#include "../SF_src/Point.h"

namespace student {

struct Vector final
{
  float x;
  float y;
  float z;

  Vector(float x, float y, float z)
      : x(x)
      , y(y)
      , z(z)
  {}

  Vector()
      : x(0)
      , y(0)
      , z(0)
  {}

  Vector(const Vector& other)
      : x(other.x)
      , y(other.y)
      , z(other.z)
  {}

  Vector(float d)
      : Vector(d, d, d)
  {}

  Vector Normalized() const
  {
    float inv_m = 1.0f / Magnitude();
    return Vector(x * inv_m, y * inv_m, z * inv_m);
  }

  float SquareMagnitude() const { return x * x + y * y + z * z; }

  float Magnitude() const { return sqrt(SquareMagnitude()); }

  Vector CrossProduct(const Vector& other) const
  {
    return Vector(y * other.z - z * other.y,
                  z * other.x - x * other.z,
                  x * other.y - y * other.x);
  }

  Vector Scale(const Vector& other) const
  {
    return Vector(x * other.x, y * other.y, z * other.z);
  }

  float Dot(const Vector& other) const
  {
    return x * other.x + y * other.y + z * other.z;
  }

  // adds two vectors
  Vector operator+(const Vector& other) const
  {
    return Vector(x + other.x, y + other.y, z + other.z);
  }

  // adds another vector to this vector specifically
  Vector& operator+=(const Vector& other)
  {
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
  }

  // subtracts two vectors
  Vector operator-(const Vector& other) const
  {
    return Vector(x - other.x, y - other.y, z - other.z);
  }

  // subtracts this vector specifically with another vector
  Vector& operator-=(const Vector& other)
  {
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
  }

  // uses scalar multiplication on a vector
  Vector operator*(const float f) const { return Vector(x * f, y * f, z * f); }

  // uses scalar multiplication on this vector specifically
  Vector& operator*=(const float f)
  {
    x *= f;
    y *= f;
    z *= f;

    return *this;
  }

  Vector operator/(const float f) const { return Vector(x / f, y / f, z / f); }

  Vector operator-() const { return Vector(-x, -y, -z); }

  bool operator==(const Vector& other) const
  {
    return x == other.x && y == other.y && z == other.z;
  }

  // implicit conversions to Henrik's Point class...
  // because he didn't put it in a proper namespace...
  Vector(const ::Point& p)
      : x(p.mX)
      , y(p.mY)
      , z(p.mZ)
  {}

  Vector& operator=(const ::Point& p)
  {
    x = p.mX;
    y = p.mY;
    z = p.mZ;

    return *this;
  }

  operator ::Point() { return ::Point(x, y, z); }
};

// easy peasy terminology correctness
using Point = Vector;

}  // namespace student

#endif  // !STUDENT_VECTOR_H
