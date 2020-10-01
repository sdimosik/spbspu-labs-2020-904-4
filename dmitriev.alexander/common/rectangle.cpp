#include <stdexcept>
#include <cmath>
#include "rectangle.hpp"
#include "utils.hpp"

namespace dmitriev
{
  Rectangle::Rectangle(const point_t &pos, const double width, const double height) :
    pos_(pos),
    width_(width),
    height_(height),
    angle_(0)
  {
    if (width <= 0 || height <= 0)
    {
      throw std::invalid_argument("Invalid argument was given.");
    }
  }

  double Rectangle::getArea() const noexcept
  {
    return width_ * height_;
  }

  rectangle_t Rectangle::getFrameRect() const noexcept
  {
    return {fabs(width_ * cos(angle_) + height_ * sin(angle_)),
            fabs(width_ * sin(angle_) + height_ * cos(angle_)), pos_};
  }

  void Rectangle::move(const point_t &point) noexcept
  {
    pos_ = point;
  }

  void Rectangle::move(const double x, const double y) noexcept
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

  void Rectangle::rotate(const double angle) noexcept
  {
    angle_ += utils::toRadians(angle);
    const double full_circle = utils::toRadians(360);
    angle_ = fmod(angle_, full_circle);
    if (angle_ < 0)
    {
      angle_ += full_circle;
    }
  }
}
