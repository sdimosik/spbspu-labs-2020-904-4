#include "circle.hpp" 
#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>

namespace spasoevich
{
  Circle::Circle(const point_t& center, double radius) :
    center_(center),
    radius_(radius)
  {
    if (radius_ <= 0)
    {
      throw std::invalid_argument("Dimensions can't be negative or equal to zero. ");
    }
  }

  double Circle::getArea() const
  {
    return (radius_ * radius_ * M_PI);
  }

  rectangle_t Circle::getFrameRect() const
  {
    return rectangle_t{ center_, radius_ * 2, radius_ * 2 };
  }

  void Circle::move(double dx, double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }

  void Circle::move(const point_t& pt)
  {
    center_ = pt;
  }

  void Circle::scale(const double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument("Coefficent can't be less or equal to zero. ");
    }
    radius_ = radius_ * coefficient;
  }
}
