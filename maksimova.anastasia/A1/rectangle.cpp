#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(double width, double height, const point_t &pos) :
  width_(width),
  height_(height),
  position_(pos)
{
  if (width_ <= 0 || height_ <= 0)
  {
    throw std::invalid_argument("Invalid rectangle parameters, width = " + std::to_string(width_) + " height = " + std::to_string(height_));
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {width_, height_, position_};
}

void Rectangle::move(const point_t &pos)
{
  position_ = pos;
}

void Rectangle::move(double dx, double dy)
{
  position_.x += dx;
  position_.y += dy;
}

void Rectangle::print()
{
  std::cout << "Width = " << width_ << ", " << "Height = " << height_ << ", "
      << "Position (" << position_.x << ", " << position_.y << ")\n";
}
