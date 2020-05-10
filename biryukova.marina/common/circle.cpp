#include "circle.hpp"
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>
#include <string>

namespace biryukova
{
  Circle::Circle(const point_t& centre, double radius) :
    radius_(radius),
    centre_(centre)
  {
    if (radius_ <= 0)
    {
      throw std::invalid_argument("Radius of circle must be positive. Invalid radius: "
          + std::to_string(radius));
    }
  }

  double Circle::getArea() const noexcept
  {
    return (M_PI * radius_ * radius_);
  }

  rectangle_t Circle::getFrameRect() const noexcept
  {
    return {radius_ * 2, radius_ * 2 , centre_};
  }

  void Circle::move(const point_t& centre) noexcept
  {
    centre_ = centre;
  }

  void Circle::move(double x, double y) noexcept
  {
    centre_.x += x;
    centre_.y += y;
  }

  void Circle::print() const
  {
    std::cout << "Circle: radius " << radius_
        << ", centre (" << centre_.x << ";" << centre_.y << ")\n";
  }

  void Circle::scale(double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument("Coefficient of scale must be positive. Invalid coefficient: "
          + std::to_string(coefficient));
    }
    radius_ *= coefficient;
  }

  double Circle::getRadius() const noexcept
  {
    return radius_;
  }

  point_t Circle::getCentre() const noexcept
  {
    return centre_;
  }
}
