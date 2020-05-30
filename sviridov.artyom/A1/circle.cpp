#define _USE_MATH_DEFINES
#include "circle.hpp"
#include <iostream>
#include <cmath>
#include <cassert>

double Circle::getArea() const
{
  return rad_ * rad_ * M_PI;
}

rectangle_t Circle::getFrameRect() const
{
  return { pos_, 2 * rad_, 2 * rad_ };
}

Circle::Circle(const point_t& pos, double rad) :
  Shape(pos), rad_(rad)
{
  assert(rad_ >=0);
}

void Circle::getInform(std::ostream& out) const
{
  out << "Circle";
  Shape::getInform(out);
  out << "radius = " << rad_;
}

std::ostream& operator<<(std::ostream& out, const Circle& out_cir)
{
  out_cir.getInform(out);
  return out;
}
