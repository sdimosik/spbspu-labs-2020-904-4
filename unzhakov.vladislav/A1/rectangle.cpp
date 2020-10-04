#include "rectangle.hpp"

#include <iostream>
#include <string>

Rectangle::Rectangle(double width, double height, const point_t& pos) :
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

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_t{ width_, height_, pos_ };
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

void Rectangle::move(const double x, const double y)
{
  pos_.x += x;
  pos_.y += y;
}

void Rectangle::move(const point_t& center)
{
  pos_ = center;
}

void Rectangle::printData() const
{
  std::cout << "Rectangle width: " << width_ << '\n'
      << "Rectangle height: " << height_ << '\n'
      << "Rectangle center: {" << pos_.x << ", " << pos_.y << "}\n";
}

void Rectangle::printFrameRectangle() const
{
  std::cout << "Rectangle frame for rectangle: height = " << getFrameRect().height
      << ", width = " << getFrameRect().width << ", center = {" << getFrameRect().pos.x
      << ", " << getFrameRect().pos.y << "}\n";
}

void Rectangle::printArea() const
{
  std::cout << "Rectangle area = " << getArea() << '\n';
}
