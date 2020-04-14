#include "circle.hpp"
#include <cassert>
#include <cmath>

Circle::Circle(double radius, const point_t& centre) :
  radius_(radius),
  centre_(centre)
{
  assert(radius > 0);
}

void Circle::print(std::ostream& out) const
{
  out << "Circle ( radius_ = " << radius_ << "; centre_(" << centre_.x << ", " << centre_.y << "))";
}

double Circle::getArea() const
{
  return (M_PI * pow(radius_, 2));
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{ radius_ * 2, radius_ * 2, centre_ };
}

void Circle::move(const point_t& newPosition)
{
  centre_ = newPosition;
}

void Circle::move(double dx, double dy)
{
  centre_.x += dx;
  centre_.y += dy;
}
