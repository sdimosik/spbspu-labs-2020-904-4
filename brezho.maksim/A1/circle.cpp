#include "circle.hpp"
#include <stdexcept>
#include <cmath>

Circle::Circle(const point_t& pos, double radius) :
  pos_{ pos },
  radius_(radius)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("The radius of the circle must be a positive number.");
  }
}

void Circle::move(const point_t& pos)
{
  pos_ = pos;
}

void Circle::move(double x, double y)
{
  pos_.x += x;
  pos_.y += y;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{ 2 * radius_, 2 * radius_, pos_ };
}

double Circle::getRadius() const
{
  return radius_;
}

void Circle::setRadius(double radius)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("The radius of the circle must be a positive number.");
  }
  radius_ = radius;
}

point_t Circle::getPosition() const
{
  return pos_;
}

double Circle::getArea() const
{
  return (radius_ * radius_ * M_PI);
}
