#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const double width, const double height, const point_t& pos) :
  width_(width),
  height_(height),
  pos_(pos)
{
  if (width <= 0 || height <= 0)
  {
    throw std::invalid_argument("Height and width must be positive.");
  }
}

double Rectangle::getWidth() const
{
  return width_;
}

double Rectangle::getHeight() const
{
  return height_;
}

point_t Rectangle::getPosition() const
{
  return pos_;
}

double Rectangle::getArea() const
{
  return (height_ * width_);
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_t{width_, height_, pos_};
}

void Rectangle::move(const double x, const double y)
{
  pos_ = {pos_.x + x, pos_.y + y};
}

void Rectangle::move(const point_t &pos)
{
  pos_ = pos;
}
