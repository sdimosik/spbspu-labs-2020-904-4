#include "circle.hpp"
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <string>  

namespace brezho
{
  Circle::Circle(const point_t& pos, double radius) :
    pos_{ pos },
    radius_(radius)
  {
    if (radius <= 0)
    {
      throw std::invalid_argument("The radius of the circle must be a positive number. Radius = " + std::to_string(radius));
    }
  }

  void Circle::move(const point_t& pos) noexcept
  {
    pos_ = pos;
  }

  void Circle::move(double x, double y) noexcept
  {
    pos_.x += x;
    pos_.y += y;
  }

  rectangle_t Circle::getFrameRect() const noexcept
  {
    return rectangle_t{ 2 * radius_, 2 * radius_, pos_ };
  }

  double Circle::getRadius() const noexcept
  {
    return radius_;
  }

  void Circle::setRadius(double radius)
  {
    if (radius <= 0)
    {
      throw std::invalid_argument("The radius of the circle must be a positive number. Radius = " + std::to_string(radius));
    }
    radius_ = radius;
  }

  point_t Circle::getPosition() const noexcept
  {
    return pos_;
  }

  double Circle::getArea() const noexcept
  {
    return (radius_ * radius_ * M_PI);
  }

  void Circle::scale(double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument("Coefficient of scale must be positive number. Coefficient = " + std::to_string(coefficient));
    }
    radius_ *= coefficient;
  }
}
