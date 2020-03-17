#include "circle.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

Circle::Circle(double radius, const point_t &pos) :
  radius_(radius),
  pos_(pos)
{
  if (radius <= 0.0)
  {
    std::string exc = "Invalid radius value in circle = " + std::to_string(radius) + '\n';
    throw std::invalid_argument(exc);
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{2 * radius_, 2 * radius_, pos_};
}

void Circle::move(const point_t &center)
{
  pos_ = center;
}

void Circle::move(double x, double y)
{
  pos_.x += x;
  pos_.y += y;
}

void Circle::printData() const
{
  std::cout << "Circle radius: " << radius_ << '\n'
    << "Circle center: (" << pos_.x << ", " << pos_.y << ")\n";
}

void Circle::printFrameRect() const
{
  std::cout << "Frame rectangle of circle: height = " << getFrameRect().height
    << ", width = " << getFrameRect().width << ", center = (" << getFrameRect().pos.x
    << ", " << getFrameRect().pos.y << ")\n";
}
