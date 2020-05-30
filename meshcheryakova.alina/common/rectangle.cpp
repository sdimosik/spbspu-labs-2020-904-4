#include "rectangle.hpp"

namespace  meshcheryakova
{
  Rectangle::Rectangle(double width, double height, const point_t &spot) :
    width_(width),
    height_(height),
    pos_(spot)
  {
    if (width_ <= 0.0)
    {
      throw std::invalid_argument("Invalid width: " + std::to_string(width_));
    }
    if (height_ <= 0.0)
    {
      throw std::invalid_argument("Invalid height: " + std::to_string(height_));
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

  void Rectangle::move(double x, double y) noexcept
  {
    pos_.x += x;
    pos_.y += y;
  }

  void Rectangle::move(const point_t &spot) noexcept
  {
    pos_ = spot;
  }

  void Rectangle::printSpot(std::ostream &out)
  {
    out << "(" << pos_.x << "," << pos_.y << ")\n";
  }

  void Rectangle::scale(double coefficient)
  {
    if (coefficient <= 0.0)
    {
      throw std::invalid_argument("Invalid coefficient: " + std::to_string(coefficient));
    }
    width_ *= coefficient;
    height_ *= coefficient;
  }

  void Rectangle::printParametersWithoutSpot(std::ostream &out)
  {
    out << " Parameters of rectangle: width = " << width_ << " height = " << height_ << '\n';
  }
}

