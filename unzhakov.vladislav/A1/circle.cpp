#define _USE_MATH_DEFINES

#include "circle.hpp"

#include <iostream>
#include <string>
#include <cmath>

Circle::Circle(const double radius, const point_t& pos) :
  radius_(radius),
  pos_(pos)
{
  if (radius <= 0.0)
  {
    throw std::invalid_argument("Invalid radius value in circle = " + std::to_string(radius) + '\n');
  }
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{ 2 * radius_, 2 * radius_, pos_ };
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

void Circle::move(const double x, const double y)
{
  pos_.x += x;
  pos_.y += y;
}

void Circle::move(const point_t& center)
{
  pos_ = center;
}

void Circle::printData() const
{
  std::cout << "Circle radius: " << radius_ << "  "
      << "Circle center: {" << pos_.x << ", " << pos_.y << "}\n";
}

void Circle::printFrameRectangle() const
{
  std::cout << "Rectangular circle frame: height = " << getFrameRect().height
      << ", width = " << getFrameRect().width << ", center = {" << getFrameRect().pos.x
      << ", " << getFrameRect().pos.y << "}\n";
}

void Circle::printArea() const
{
  std::cout << "Area of a circle = " << getArea() << '\n';
}
