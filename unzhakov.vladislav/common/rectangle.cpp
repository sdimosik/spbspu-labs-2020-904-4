#include "rectangle.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

unzhakov::Rectangle::Rectangle(double width, double height, const point_t &pos):
  width_(width),
  height_(height),
  pos_(pos)
{
  if (width <= 0.0)
  {
    throw std::invalid_argument("Invalid width value in circle = " + std::to_string(width) + '\n');
  }
  if (height <= 0.0)
  {
    throw std::invalid_argument("Invalid radius value in circle = " + std::to_string(height) + '\n');
  }
}

unzhakov::rectangle_t unzhakov::Rectangle::getFrameRect() const
{
  return rectangle_t{width_, height_, pos_};
}

double unzhakov::Rectangle::getArea() const
{
  return width_ * height_;
}

unzhakov::point_t unzhakov::Rectangle::getCenter() const
{
  return pos_;
}

void unzhakov::Rectangle::move(double x, double y)
{
  pos_.x += x;
  pos_.y += y;
}

void unzhakov::Rectangle::move(const point_t &center)
{
  pos_ = center;
}

void unzhakov::Rectangle::scale(const double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Invalid coefficient in rectangle = " + std::to_string(coefficient) + '\n');
  }
  width_ *= coefficient;
  height_ *= coefficient;
}

void unzhakov::Rectangle::printData() const
{
  std::cout << "Rectangle width: " << width_ << '\n'
      << "Rectangle height: " << height_ << '\n'
      << "Rectangle center: {" << pos_.x << ", " << pos_.y << "}\n";
}

void unzhakov::Rectangle::printFrameRectangle() const
{
  std::cout << "Rectangle frame for rectangle: height = " << getFrameRect().height
      << ", width = " << getFrameRect().width << ", center = {" << getFrameRect().pos.x
      << ", " << getFrameRect().pos.y << "}\n";
}

void unzhakov::Rectangle::printArea() const
{
  std::cout << "Rectangle area = " << getArea() << '\n';
}
