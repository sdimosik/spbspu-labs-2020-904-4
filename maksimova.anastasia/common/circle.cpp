#include "circle.hpp"
#include <cmath>
#include <stdexcept>

namespace maksimova
{
  Circle::Circle(const double radius, const point_t &pos) :
    radius_(radius),
    center_(pos)
  {
    if (radius_ <= 0)
    {
      throw std::invalid_argument("Invalid circle parameters, radius = " + std::to_string(radius));
    }
  }

  double Circle::getArea() const
  {
    return M_PI * radius_ * radius_;
  }

  rectangle_t Circle::getFrameRect() const
  {
    return {2 * radius_, 2 * radius_, center_};
  }

  void Circle::move(const point_t &pos)
  {
    center_ = pos;
  }

  void Circle::move(const double dx, const double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }

  void Circle::print() const
  {
    std::cout << "Radius = " << radius_ << "\n"
        << "Center (" << center_.x << ", " << center_.y << ")\n";
  }

  double Circle::getRadius() const
  {
    return radius_;
  }

  point_t Circle::getCenter() const
  {
    return center_;
  }

  void Circle::scale(const double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument("Invalid scaling options = " + std::to_string(coefficient));
    }
    else
    {
      radius_ *= coefficient;
    }
  }

  void Circle::rotate(const double) noexcept
  {}
}
