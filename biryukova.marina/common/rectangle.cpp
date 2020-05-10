#include "rectangle.hpp"
#include <iostream>
#include <string>

namespace biryukova
{
  Rectangle::Rectangle(const point_t& centre, double width, double height) :
    rectangle_(rectangle_t{ width, height, centre })
  {
    testValidParameters(this->rectangle_);
  }

  Rectangle::Rectangle(const rectangle_t& rectangle) :
    rectangle_(rectangle)
  {
    testValidParameters(this->rectangle_);
  }


  double Rectangle::getArea() const noexcept
  {
    return (rectangle_.width * rectangle_.height);
  }

  rectangle_t Rectangle::getFrameRect() const noexcept
  {
    return rectangle_;
  }

  void Rectangle::move(const point_t& centre) noexcept
  {
    rectangle_.pos = centre;
  }

  void Rectangle::move(double x, double y) noexcept
  {
    rectangle_.pos.x += x;
    rectangle_.pos.y += y;
  }

  void Rectangle::print() const
  {
    std::cout << "Rectangle: width " << rectangle_.width
        << ", height " << rectangle_.height
        << ", centre (" << rectangle_.pos.x << ";" << rectangle_.pos.y << ")\n";
  }

  void Rectangle::testValidParameters(const rectangle_t& rectangle)
  {
    if (rectangle.height <= 0)
    {
      throw std::invalid_argument("Height of rectangle must be positive. Invalid height: "
          + std::to_string(rectangle.height));
    }
    if (rectangle.width <= 0)
    {
      throw std::invalid_argument("Width of rectangle must be positive. Invalid width: "
          + std::to_string(rectangle.width));
    }
  }

  void Rectangle::scale(double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument("Coefficient of scale must be positive. Invalid coefficient: "
          + std::to_string(coefficient));
    }
    rectangle_.width *= coefficient;
    rectangle_.height *= coefficient;
  }

  double Rectangle::getHeight() const noexcept
  {
    return rectangle_.height;
  }

  double Rectangle::getWidth() const noexcept
  {
    return rectangle_.width;
  }

  point_t Rectangle::getCentre() const noexcept
  {
    return rectangle_.pos;
  }
}
