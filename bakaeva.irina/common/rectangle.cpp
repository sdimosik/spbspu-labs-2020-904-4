#include "rectangle.hpp"
#include <iostream>
#include <stdexcept>

namespace bakaeva
{
  Rectangle::Rectangle(double width, double height, const point_t &pos) :
    width_(width),
    height_(height),
    pos_(pos)
  {
    if (width <= 0.0)
    {
      throw std::invalid_argument(std::string("Invalid width value in rectangle = ") += std::to_string(width));
    }
    if (height <= 0.0)
    {
      throw std::invalid_argument(std::string("Invalid height value in rectangle = ") += std::to_string(height));
    }
  }

  double Rectangle::getArea() const noexcept
  {
    return width_ * height_;
  }

  rectangle_t Rectangle::getFrameRect() const noexcept
  {
    return rectangle_t{width_, height_, pos_};
  }

  void Rectangle::move(const point_t &center) noexcept
  {
    pos_ = center;
  }

  void Rectangle::move(double x, double y) noexcept
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
    std::cout << "Frame rectangle of rectangle: height = " << getFrameRect().height
        << ", width = " << getFrameRect().width << ", center = (" << getFrameRect().pos.x
        << ", " << getFrameRect().pos.y << ")\n";
  }

  void Rectangle::scale(const double coefficient)
  {
    if (coefficient <= 0.0)
    {
      throw std::invalid_argument(std::string("Invalid coefficient value in rectangle = ") += std::to_string(coefficient));
    }
    width_ *= coefficient;
    height_ *= coefficient;
  }
}


