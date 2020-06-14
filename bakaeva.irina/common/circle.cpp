#include "circle.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

namespace bakaeva
{
  Circle::Circle(double radius, const point_t &pos):
    radius_(radius),
    pos_(pos)
  {
    if (radius <= 0.0)
    {
      throw std::invalid_argument(std::string("Invalid radius value in circle = ") += std::to_string(radius));
    }
  }

  double Circle::getArea() const noexcept
  {
    return M_PI * radius_ * radius_;
  }

  rectangle_t Circle::getFrameRect() const noexcept
  {
    return rectangle_t{2 * radius_, 2 * radius_, pos_};
  }

  void Circle::move(const point_t &center) noexcept
  {
    pos_ = center;
  }

  void Circle::move(double x, double y) noexcept
  {
    pos_.x += x;
    pos_.y += y;
  }

  void Circle::printData() const
  {
    std::cout << "Circle:\n" << "Circle radius: " << radius_ << '\n'
        << "Circle center: (" << pos_.x << ", " << pos_.y << ")\n";
  }

  void Circle::printFrameRect() const
  {
    std::cout << "Frame rectangle of circle: height = " << getFrameRect().height
        << ", width = " << getFrameRect().width << ", center = (" << getFrameRect().pos.x
        << ", " << getFrameRect().pos.y << ")\n";
  }

  void Circle::scale(const double coefficient)
  {
    if (coefficient <= 0.0)
    {
      throw std::invalid_argument(std::string("Invalid coefficient value in circle = ")
         += std::to_string(coefficient));
    }
    radius_ *= coefficient;
  }

  void Circle::rotate(const double) noexcept
  {}

  point_t Circle::getCenter() const noexcept
  {
    return pos_;
  }
}
