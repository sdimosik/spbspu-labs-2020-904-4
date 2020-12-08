#include "shape.hpp"
#include "circle.hpp"
#include "square.hpp"
#include "triangle.hpp"

Shape::Shape(Point center) :
  center_(center)
{}

bool Shape::isMoreLeft(const Shape& rhs) const
{
  return center_.x < rhs.center_.x;
}

bool Shape::isUpper(const Shape& rhs) const
{
  return center_.y > rhs.center_.y;
}

Point Shape::getCenter() const
{
  return center_;
}
