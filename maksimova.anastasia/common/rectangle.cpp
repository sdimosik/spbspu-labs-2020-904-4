#include "rectangle.hpp"
#include <stdexcept>

namespace maksimova
{
  Rectangle::Rectangle(const double width, const double height, const point_t &pos) :
    width_(width),
    height_(height),
    position_(pos)
  {
    if (width_ <= 0 || height_ <= 0)
    {
      throw std::invalid_argument("Invalid rectangle parameters, width = "
          + std::to_string(width_) + " height = " + std::to_string(height_));
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

  void Rectangle::move(const double dx, const double dy)
  {
    position_.x += dx;
    position_.y += dy;
  }

  void Rectangle::print() const
  {
    std::cout << "Width = " << width_ << ", " << "Height = " << height_ << ", "
        << "Position (" << position_.x << ", " << position_.y << ")\n";
  }

  void Rectangle::scale(const double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument("Invalid scaling options = " + std::to_string(coefficient));
    }
    else
    {
      width_ *= coefficient;
      height_ *= coefficient;
    }
  }

  double Rectangle::get_width() const
  {
    return width_;
  }

  double Rectangle::get_height() const
  {
    return height_;
  }
}
