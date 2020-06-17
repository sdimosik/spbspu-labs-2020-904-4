#include <math.h>
#include "rectangle.hpp"

namespace  meshcheryakova
{
  Rectangle::Rectangle(double width, double height, const point_t &spot) :
    width_(width),
    height_(height),
    pos_(spot),
    angle_(0)
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
    double angle = M_PI * angle_ / 180;
    double sin = fabs(std::sin(angle));
    double cos = fabs(std::cos(angle));
    return rectangle_t{(width_ * cos) + (height_ * sin), (width_ * sin) + (height_ * cos), pos_};
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

  void Rectangle::rotate(double angle) noexcept
  {
    double full_turn = 360;

    angle_ += angle;
    angle_ = (angle_ < 0) ? (full_turn + fmod(angle_, full_turn)) : (fmod(angle_, full_turn));

  }
}

