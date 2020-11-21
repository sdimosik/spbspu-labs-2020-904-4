#include "circle.hpp"

#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <cmath>

unzhakov::Circle::Circle(double radius, const point_t &pos):
  radius_(radius),
  pos_(pos)
{
  if (radius <= 0.0)
  {
    throw std::invalid_argument("Invalid radius value in circle = " + std::to_string(radius) + '\n');
  }
}

unzhakov::rectangle_t unzhakov::Circle::getFrameRect() const
{
  return rectangle_t{2 * radius_, 2 * radius_, pos_};
}

double unzhakov::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

unzhakov::point_t unzhakov::Circle::getCenter() const
{
  return pos_;
}

void unzhakov::Circle::move(double x, double y)
{
  pos_.x += x;
  pos_.y += y;
}

void unzhakov::Circle::move(const point_t &center)
{
  pos_ = center;
}

void unzhakov::Circle::scale(const double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Invalid coefficient in circle = " + std::to_string(coefficient) + '\n');
  }
  radius_ *= coefficient;
}

void unzhakov::Circle::rotate(double)
{}


void unzhakov::Circle::printData() const
{
  std::cout << "Circle radius: " << radius_ << "  "
      << "Circle center: {" << pos_.x << ", " << pos_.y << "}\n";
}

void unzhakov::Circle::printFrameRectangle() const
{
  std::cout << "Rectangular circle frame: height = " << getFrameRect().height
      << ", width = " << getFrameRect().width << ", center = {" << getFrameRect().pos.x
      << ", " << getFrameRect().pos.y << "}\n";
}

void unzhakov::Circle::printArea() const
{
  std::cout << "Area of a circle = " << getArea() << '\n';
}
