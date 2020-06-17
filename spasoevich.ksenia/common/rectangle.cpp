#include "rectangle.hpp"
#define _USE_MATH_DEFINES
#include <stdexcept>
#include <cmath>
#include <iostream>

const double fullCircle = 360.0;

namespace spasoevich
{
  Rectangle::Rectangle(const point_t& center, const double width, const double height) :
    rect({ center, width, height }),
    angle_(0.0)
  {
    if (width <= 0 || height <= 0)
    {
      throw std::invalid_argument(" Dimensions can't be negaitve or equal to zero. ");
    }
  }

  double Rectangle::getArea() const noexcept
  {
    return (rect.width * rect.height);
  }

  rectangle_t Rectangle::getFrameRect() const noexcept
  {
    double angleInRadians = angle_ * M_PI / (fullCircle / 2);
    return rectangle_t{ rect.pos, rect.width * cos(angleInRadians) + rect.height * sin(angleInRadians),
       rect.width * sin(angleInRadians) + rect.height * cos(angleInRadians) };
  }

  void Rectangle::move(const double dx, const double dy) noexcept
  {
    rect.pos.x += dx;
    rect.pos.y += dy;
  }

  void Rectangle::move(const point_t& pt) noexcept
  {
    rect.pos = pt;
  }

  void Rectangle::scale(const double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument("Coefficent can't be less or equal to zero. ");
    }
    else
    {
      rect.width = rect.width * coefficient;
      rect.height = rect.height * coefficient;
    }
  }

  void Rectangle::rotate(const double angle) noexcept
  {
    angle_ += angle;
    angle_ = (angle_ < 0.0) ? (fullCircle + fmod(angle_, fullCircle)) : fmod(angle_, fullCircle);
  }
}
