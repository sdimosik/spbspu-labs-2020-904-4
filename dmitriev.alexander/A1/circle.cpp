#include "circle.hpp"
#include <cmath>
#include <stdexcept>

Circle::Circle(const point_t &pos, double radius) :
  pos_(pos),
  radius_(radius)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("Invalid argument was given.");
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{radius_ * 2, radius_ * 2, pos_};
}

void Circle::move(const point_t &point)
{
  pos_ = point;
}

void Circle::move(double x, double y)
{
  pos_.x += x;
  pos_.y += y;
}
