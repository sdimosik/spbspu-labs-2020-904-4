#include "circle.hpp"
#include <cmath>
#include <stdexcept>

namespace dmitriev
{
  Circle::Circle(const point_t &pos, double radius) :
    pos_(pos),
    radius_(radius)
  {
    if (radius <= 0)
    {
      throw std::invalid_argument("Invalid argument was given.");
    }
  }

  double Circle::getArea() const noexcept
  {
    return M_PI * radius_ * radius_;
  }

  rectangle_t Circle::getFrameRect() const noexcept
  {
    return rectangle_t{radius_ * 2, radius_ * 2, pos_};
  }

  void Circle::move(const point_t &point) noexcept
  {
    pos_ = point;
  }

  void Circle::move(const double x, const double y) noexcept
  {
    pos_.x += x;
    pos_.y += y;
  }

  void Circle::scale(const double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Invalid scale factor was given. Must be positive.");
    }
    radius_ *= factor;
  }
}
