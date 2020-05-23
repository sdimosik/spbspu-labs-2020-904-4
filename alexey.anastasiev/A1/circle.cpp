#include "circle.hpp"
#include <stdexcept>
#include <cmath>



Circle::Circle(const double radius, const point_t& pos):
  radius_(radius),
  pos_(pos)
{
  if (radius<=0)
    {
      throw std::invalid_argument("Radius must be positive.");
    }
}

double Circle::getRadius() const
{
  return radius_;
}

point_t Circle::getPosition() const
{
  return pos_;
}
  
double Circle::getArea() const
{
  return (M_PI * radius_ * radius_);
}
rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{ radius_ * 2 , radius_ * 2,pos_ };
}

void Circle::move(const point_t& pos)
{
  pos_ = pos;
}

void Circle::move (const double x, const double y)
{
  pos_ = {pos_.x + x, pos_.y + y};
}
