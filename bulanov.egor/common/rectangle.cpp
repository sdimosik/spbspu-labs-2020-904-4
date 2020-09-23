#include "rectangle.hpp"
#include <stdexcept>
#include <iostream>
#include <cmath>

namespace bulanov
{

  const double  CIRCLE_ANGLE = 360.0;

  Rectangle::Rectangle(const point_t &center, double width, double height) :
    width_(width),
    height_(height),
    pos_{center.x, center.y},
    angle_(0)
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

  void Rectangle::move(const point_t &center) noexcept
  {
    pos_ = center;
  }

  void Rectangle::move(const double x, const double y) noexcept
  {
    pos_.x += x;
    pos_.y += y;
  }

  double Rectangle::getArea() const noexcept
  {
    return (height_ * width_);
  }

  rectangle_t Rectangle::getFrameRect() const noexcept
  {
    double RadAngle = angle_ * M_PI / (CIRCLE_ANGLE / 2);
    return {height_ * fabs(sin(RadAngle)) + width_ * fabs(cos(RadAngle)),
            width_ * fabs(sin(RadAngle)) + height_ * fabs(cos(RadAngle)), pos_};
  }

  void Rectangle::printInform() const
  {
    std::cout << "Rectangle width: " << width_ << "; Rectangle height: " << height_
        << "; Rectangle center: (" << pos_.x << ", " << pos_.y << ")\n";
  }

  void Rectangle::printFrameInform() const
  {
    std::cout << "Rect frame information:   width = " << getFrameRect().width
        << "; height = " << getFrameRect().height << "; center = (" << getFrameRect().pos.x
        << ", " << getFrameRect().pos.y << ")\n";
  }

  point_t Rectangle::getCenter() const noexcept
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

  void Rectangle::rotate(const double angle) noexcept
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

  double Rectangle::getAngle() const noexcept
  {
    return angle_;
  }

}

