#include "circle.hpp"
#include <cmath>

namespace lovkacheva
{
  Circle::Circle(double radius, const point_t& centre) :
    radius_(radius),
    centre_(centre)
  {
    if (radius <= 0)
    {
      throw std::invalid_argument(
          "The radius of the circle must be positive (radius = " + std::to_string(radius) + ")");
    }
  }

  void Circle::print(std::ostream& out) const
  {
    out << "Circle ( radius_ = " << radius_ << "; centre_(" << centre_.x << ", " << centre_.y << "))";
  }

  double Circle::getArea() const noexcept
  {
    return (M_PI * pow(radius_, 2));
  }

  rectangle_t Circle::getFrameRect() const noexcept
  {
    return rectangle_t{radius_ * 2, radius_ * 2, centre_};
  }

  void Circle::move(const point_t& newPosition) noexcept
  {
    centre_ = newPosition;
  }

  void Circle::move(double dx, double dy) noexcept
  {
    centre_.x += dx;
    centre_.y += dy;
  }

  void Circle::scale(double coefficient)
  {
    if (coefficient <= 0.0)
    {
      throw std::invalid_argument(
          "The coefficient must be positive (coefficient = " + std::to_string(coefficient) + ")");
    }
    radius_ *= coefficient;
  }

  void Circle::rotate(double) noexcept
  {}
}
