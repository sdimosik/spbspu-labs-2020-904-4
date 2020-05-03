#include "rectangle.hpp"
#include <stdexcept>

namespace dmitriev
{
  Rectangle::Rectangle(const point_t &pos, const double width, const double height) :
    pos_(pos),
    width_(width),
    height_(height)
  {
    if (width <= 0 || height <= 0)
    {
      throw std::invalid_argument("Invalid argument was given.");
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

  void Rectangle::move(const point_t &point)
  {
    pos_ = point;
  }

  void Rectangle::move(const double x, const double y)
  {
    pos_.x += x;
    pos_.y += y;
  }

  void Rectangle::scale(const double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Invalid scale factor was given. Must be positive.");
    }
    width_ *= factor;
    height_ *= factor;
  }
}
