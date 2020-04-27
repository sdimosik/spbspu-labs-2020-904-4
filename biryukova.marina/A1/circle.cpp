#include "circle.hpp"
#include <cassert>
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>

Circle::Circle(const point_t& centre, double radius) :
  radius_(radius),
  centre_(centre)
{
  assert(radius_ > 0);
}

double Circle::getArea() const
{
  return (M_PI * radius_ * radius_);
}

rectangle_t Circle::getFrameRect() const
{
  return { radius_ * 2, radius_ * 2 , centre_ };
}

void Circle::move(const point_t& centre)
{
  centre_ = centre;
}

void Circle::move(double x, double y)
{
  centre_.x += x;
  centre_.y += y;
}

void Circle::print() const
{
  std::cout << "Circle: radius " << radius_ 
    << ", centre (" << centre_.x << ";" << centre_.y << ")\n";
}
