#include "rectangle.hpp"
#include <string>
#include <stdexcept>

Rectangle::Rectangle(double width, double height, const point_t &pos) :
  width_(width),
  height_(height),
  pos_(pos)

{
  if (width_ <= 0.0)
  {
    throw std::invalid_argument(std::string("Invalid parameter: width should be positive, width = "
      + std::to_string(width_)));
  }
  if (height_ <= 0.0)
  {
    throw std::invalid_argument(std::string("Invalid parameter: height should be positive, height = "
      + std::to_string(height_)));
  }
}

double Rectangle::getArea() const
{
  return height_ * width_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_t{width_, height_, pos_};
}

void Rectangle::move(const point_t &point)
{
  pos_ = point;
}

void Rectangle::move(double x, double y)
{
  pos_.x += x;
  pos_.y += y;
}
