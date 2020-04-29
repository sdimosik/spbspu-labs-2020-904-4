#include "circle.hpp"

#define _USE_MATH_DEFINES

#include <cmath>
#include <stdexcept>
#include <string>

namespace khilchenko
{
  Circle::Circle(double rad, const point_t &pos):
    rad_(rad),
    pos_(pos)
  {
    if (rad <= 0.0)
    {
      throw std::invalid_argument("Radius must be a positive number. Invalid radius: " + std::to_string(rad));
    }
  }

  double Circle::getArea() const
  {
    return (rad_ * rad_ * M_PI);
  }

  rectangle_t Circle::getFrameRect() const
  {
    return rectangle_t{ pos_, 2 * rad_, 2 * rad_ };
  }

  void Circle::move(const point_t &newPos)
  {
    pos_ = newPos;
  }

  void Circle::move(double x, double y)
  {
    pos_.x += x;
    pos_.y += y;
  }

  point_t Circle::getCenter() const
  {
    return point_t{ pos_.x, pos_.y };
  }
  void Circle::scale(double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument("Coefficient must be a positive number. Invalid coefficient: " + std::to_string(coefficient));
    }
    rad_ *= coefficient;
  }
}
