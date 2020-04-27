#include "rectangle.hpp"
#include <stdexcept>
#include <iostream>

namespace bulanov
{
  Rectangle::Rectangle(const point_t &center, double width, double height) :
    width_(width),
    height_(height),
    pos_{center.x, center.y}
  {
    if (width <= 0)
    {
      throw std::invalid_argument("Invalid width: " + std::to_string(width));
    }
    if (height <= 0)
    {
      throw std::invalid_argument("Invalid height: " + std::to_string(height));
    }
  }

  void Rectangle::move(const point_t &center)
  {
    pos_ = center;
  }

  void Rectangle::move(const double x, const double y)
  {
    pos_.x += x;
    pos_.y += y;
  }

  double Rectangle::getArea() const
  {
    return (height_ * width_);
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return rectangle_t{width_, height_, pos_};
  }

  void Rectangle::printInform() const
  {
    std::cout << "Rectangle width: " << width_ << "; Rectangle height: " << height_
        << "; Rectangle center: (" << pos_.x << ", " << pos_.y << ')' << std::endl;
  }

  void Rectangle::printFrameInform() const
  {
    std::cout << "Rect frame information:   width = " << getFrameRect().width
        << "; height = " << getFrameRect().height << "; center = (" << getFrameRect().pos.x
        << ", " << getFrameRect().pos.y << ')' << std::endl;
  }

  point_t Rectangle::getCenter() const
  {
    return pos_;
  }

  void Rectangle::scale(const double rate)
  {
    if (rate <= 0)
    {
      throw std::invalid_argument("Invalid rate:  " + std::to_string(rate));
    }
    width_ *= rate;
    height_ *= rate;
  }
}

