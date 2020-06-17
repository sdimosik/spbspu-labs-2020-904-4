#include "circle.hpp"
#include <cmath>

namespace  meshcheryakova
{
  Circle::Circle(const point_t &pos, double radius) :
    pos_(pos),
    radius_(radius)
  {
    if (radius <= 0.0)
    {
      throw std::invalid_argument("Invalid radius: " + std::to_string(radius));
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

  void Circle::move(double x, double y) noexcept
  {
    pos_.x += x;
    pos_.y += y;
  }

  void Circle::move(const point_t &spot) noexcept
  {
    pos_ = spot;
  }

  void Circle::printSpot(std::ostream &out)
  {
    out << "(" << pos_.x << "," << pos_.y << ")\n";
  }

  void Circle::scale(double coefficient)
  {
    if (coefficient <= 0.0)
    {
      throw std::invalid_argument("Invalid coefficient: " + std::to_string(coefficient));
    }
    radius_ *= coefficient;
  }

  void Circle::printParametersWithoutSpot(std::ostream &out)
  {
    out << "Parameters of circle: radius = " << radius_ << '\n';
  }

  void Circle::rotate(double) noexcept
  {}
}

