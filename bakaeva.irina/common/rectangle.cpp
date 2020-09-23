#include "rectangle.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

namespace bakaeva
{
  const double  FULL_CIRCLE = 360.0;

  Rectangle::Rectangle(double width, double height, const point_t &pos) :
    width_(width),
    height_(height),
    pos_(pos),
    angle_(0)
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
    double angleInRad = angle_ * M_PI / (FULL_CIRCLE / 2);
    return {fabs(width_ * cos(angleInRad) + height_ * sin(angleInRad)),
        fabs(width_ * sin(angleInRad) + height_ * cos(angleInRad)), pos_};
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
    std::cout << "Rectangle:\n" << "Rectangle width: " << width_ << '\n'
        << "Rectangle height: " << height_ << '\n'
        << "Rectangle center: (" << pos_.x << ", " << pos_.y << ")\n"
        << "Figure rotation angle: " << angle_ << '\n';
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
      throw std::invalid_argument(std::string("Invalid coefficient value in rectangle = ")
          += std::to_string(coefficient));
    }
    width_ *= coefficient;
    height_ *= coefficient;
  }

  void Rectangle::rotate(const double angle) noexcept
  {
    angle_ += angle;
    angle_ = (angle_ > 0.0) ? fmod(angle_, FULL_CIRCLE) : FULL_CIRCLE + fmod(angle_, FULL_CIRCLE);
  }

  point_t Rectangle::getCenter() const noexcept
  {
    return pos_;
  }

  double Rectangle::getAngle() const noexcept
  {
    return angle_;
  }
}


