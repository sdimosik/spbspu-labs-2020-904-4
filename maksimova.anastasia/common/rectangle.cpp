#include "rectangle.hpp"
#include <stdexcept>
#include <cmath>

namespace maksimova
{
  Rectangle::Rectangle(const double width, const double height, const point_t &pos) :
    width_(width),
    height_(height),
    position_(pos),
    angle_(0)
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

  void Rectangle::rotate(const double angle)
  {
    angle_ += angle;
    if (angle_ > 0.0)
    {
      angle_ = fmod(angle_, CIRCLE_ANGLE);
    }
    else
    {
      angle_ = CIRCLE_ANGLE + fmod(angle_, CIRCLE_ANGLE);
    }
  }

  double Rectangle::getAngle() const
  {
    return angle_;
  }

  Rectangle::Rectangle(const maksimova::rectangle_t &rectangle) :
    width_(rectangle.width),
    height_(rectangle.height),
    position_(rectangle.pos),
    angle_(0)
  {}
}
