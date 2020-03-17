#include "rectangle.hpp"
#include <iostream>
#include <stdexcept>

Rectangle::Rectangle(double width, double height, const point_t &pos) :
  width_(width),
  height_(height),
  pos_(pos)
{
  if (width <= 0.0)
  {
    std::string exc = "Invalid width value in circle = " + std::to_string(width) + '\n';
    throw std::invalid_argument(exc);
  }
  if (height <= 0.0)
  {
    std::string exc = "Invalid radius value in circle = " + std::to_string(height) + '\n';
    throw std::invalid_argument(exc);
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_t{width_, height_, pos_};
}

void Rectangle::move(const point_t &center)
{
  pos_ = center;
}

void Rectangle::move(double x, double y)
{
  pos_.x += x;
  pos_.y += y;
}

void Rectangle::printData() const
{
  std::cout << "Rectangle width: " << width_ << '\n'
    << "Rectangle height: " << height_ << '\n'
    << "Rectangle center: (" << pos_.x << ", " << pos_.y << ")\n";
}

void Rectangle::printFrameRect() const
{
  std::cout << "Frame rectangle of circle: height = " << getFrameRect().height
    << ", width = " << getFrameRect().width << ", center = (" << getFrameRect().pos.x
    << ", " << getFrameRect().pos.y << ")\n";
}



