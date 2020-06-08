#include "rectangle.hpp"
#include <stdexcept>
namespace anastasiev
{
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

  double Rectangle::getArea() const noexcept
  {
    return (height_ * width_);
  }

  rectangle_t Rectangle::getFrameRect() const noexcept
  {
    return rectangle_t{width_, height_, pos_};
  }

  void Rectangle::move(const double x, const double y) noexcept
  {
    pos_.x += x;
    pos_.y += y;
  }

  void Rectangle::move(const point_t &pos) noexcept
  {
    pos_ = pos;
  }

  void Rectangle::scale(const double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Factor of scale must be positive.");
    }
    width_ *= factor;
    height_ *= factor;
  }
}//namespace anastasiev
