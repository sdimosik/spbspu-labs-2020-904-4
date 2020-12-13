#include "shape.hpp"

#include <string>

Shape::Shape(const Point& point):
    center(point)
{}

bool Shape::isMoreLeft(const Shape& other) const noexcept
{
  return (center.x < (other.center.x));
}

bool Shape::isUpper(const Shape& other) const noexcept
{
  return (center.y > (other.center.y));
}
