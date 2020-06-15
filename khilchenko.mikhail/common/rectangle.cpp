#include "rectangle.hpp"

#define _USE_MATH_DEFINES

#include <stdexcept>
#include <string>
#include <cmath>

namespace khilchenko
{
  const double HALF_CIRCLE = 180;

  Rectangle::Rectangle(double width, double height, const point_t &pos):
    angle_(0),
    figure_(rectangle_t{ pos, width, height })
  {
    if (width <= 0.0 || height <= 0)
    {
      throw std::invalid_argument(std::string("Width and height must be positive numbers. Invalid arguments:\nWidth: ")
          + std::to_string(width) + std::string("\nHeight: ") + std::to_string(height));
    }
  }

  double Rectangle::getArea() const noexcept
  {
    return (figure_.height * figure_.width);
  }

  void Rectangle::move(const point_t &newPos) noexcept
  {
    figure_.pos = newPos;
  }

  void Rectangle::move(double x, double y) noexcept
  {
    figure_.pos.x += x;
    figure_.pos.y += y;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    double angleInRad = angle_ * M_PI / HALF_CIRCLE;
    return rectangle_t{ figure_.pos, figure_.width * cos(angleInRad) + figure_.height* sin(angleInRad),
        figure_.width * sin(angleInRad) + figure_.height* cos(angleInRad)};
  }

  point_t Rectangle::getCenter() const noexcept
  {
    return point_t{ figure_.pos.x, figure_.pos.y };
  }
  void Rectangle::scale(double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument("Coefficient must be a positive number. Invalid coefficient: " + std::to_string(coefficient));
    }
    figure_.height *= coefficient;
    figure_.width *= coefficient;
  }

  void Rectangle::rotate(double angle) noexcept
  {
    angle_ = (angle_ + angle) - (360 * int((angle_ + angle) / 360));
  }
}
