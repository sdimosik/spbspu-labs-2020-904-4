#include "circle.hpp"
#include <cmath>
#include <stdexcept>
#include <string>

namespace kichigin
{
  Circle::Circle(double radius, const point_t& position) :
    radius_(radius),
    pos_{ position }
  {
    if (radius <= 0.0)
    {
      throw std::invalid_argument(std::string("Radius of circle " + std::to_string(radius) + " must be positive"));
    }
  }

  double Circle::getRadius() const
  {
    return radius_;
  }

  point_t Circle::getPosition() const
  {
    return pos_;
  }

  double Circle::getArea() const
  {
    return (radius_ * radius_ * M_PI);
  }

  rectangle_t Circle::getFrameRect() const
  {
    return rectangle_t{ 2 * radius_, 2 * radius_, pos_ };
  }

  void Circle::setRadius(double radius)
  {
    if (radius <= 0.0)
    {
      throw std::invalid_argument(std::string("Radius of circle " + std::to_string(radius) + " must be positive"));
    }
    radius_ = radius;
  }

  void Circle::move(const point_t& position)
  {
    pos_ = position;
  }

  void Circle::move(double x, double y)
  {
    pos_.x += x;
    pos_.y += y;
  }

  void Circle::scale(double coefficient)
  {
    if (coefficient <= 0.0)
    {
      throw std::invalid_argument(std::string("Coefficient of scale" + std::to_string(coefficient) + " must be positive"));
    }
    radius_ *= coefficient;
  }
}
