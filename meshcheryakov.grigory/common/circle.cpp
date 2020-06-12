#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>
#include <string>

namespace meshcheryakov
{
  Circle::Circle(double radius, const point_t &point) :
    radius_(radius),
    point_(point)
  {
    if (radius_ <= 0.0)
    {
      throw std::invalid_argument(std::string("Radius must be positive, radius = "
          + std::to_string(radius_)));
    }
  }

  double Circle::getArea() const
  {
    return (radius_ * radius_ * M_PI);
  }

  rectangle_t Circle::getFrameRect() const
  {
    return {2.0 * radius_, 2.0 * radius_, point_};
  }

  void Circle::move(double dx, double dy)
  {
    point_.x += dx;
    point_.y += dy;
  }

  void Circle::move(const point_t &point)
  {
    point_ = point;
  }

  void Circle::scale(const double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument(std::string("Coefficient must be positive, coefficient = "
          + std::to_string(coefficient)));
    }
    radius_ *= coefficient;
  }

  point_t Circle::getPosition() const noexcept
  {
    return point_;
  }

  double Circle::getRadius() const
  {
    return radius_;
  }
}
