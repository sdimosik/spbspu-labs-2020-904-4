#include "circle.hpp" 
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdexcept>

Circle::Circle(const point_t& center, double radius) :
  center_(center),
  radius_(radius)
{
  if (radius_ <= 0)
  {
    throw std::invalid_argument("Dimensions can't be negative or equal to zero. ");
  }
}

double Circle::getArea() const
{
  return (radius_ * radius_ * M_PI);
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{ center_, radius_ * 2, radius_ * 2 };
}

void Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::move(const point_t& pt)
{
  center_ = pt;
}
