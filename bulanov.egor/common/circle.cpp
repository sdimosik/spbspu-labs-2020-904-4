#include "circle.hpp"
#include <stdexcept>
#include <cmath>
#include <iostream>

namespace bulanov
{
  Circle::Circle(double radius, const point_t &center) :
    radius_(radius),
    pos_(center)
  {
    if (radius <= 0)
    {
      throw std::invalid_argument("Invalid radius:  " + std::to_string(radius));
    }
  }

  void Circle::move(const point_t &center) noexcept
  {
    pos_ = center;
  }

  void Circle::move(const double x, const double y) noexcept
  {
    pos_.x += x;
    pos_.y += y;
  }

  double Circle::getArea() const noexcept
  {
    return (M_PI * radius_ * radius_);
  }

  rectangle_t Circle::getFrameRect() const noexcept
  {
    return rectangle_t{2 * radius_, 2 * radius_, pos_};
  }

  void Circle::printInform() const
  {
    std::cout << "Circle radius: " << radius_
        << "; Circle center: (" << pos_.x << ", " << pos_.y << ") \n";
  }

  void Circle::printFrameInform() const
  {
    std::cout << "Rect frame information:   width = " << getFrameRect().width
        << "; height = " << getFrameRect().height << "; center = (" << getFrameRect().pos.x
        << ", " << getFrameRect().pos.y << ")\n";
  }

  point_t Circle::getCenter() const noexcept
  {
    return pos_;
  }

  void Circle::scale(const double rate)
  {
    if (rate <= 0)
    {
      throw std::invalid_argument("Invalid rate:  " + std::to_string(rate));
    }
    radius_ *= rate;
  }
}





