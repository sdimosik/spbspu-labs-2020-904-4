#include "rectangle.hpp"
#include <stdexcept>
#include <string>

namespace kichigin
{
  Rectangle::Rectangle(double width, double height, const point_t& pos) :
    figure_{ width, height, pos }
  {
    if (width <= 0.0)
    {
      throw std::invalid_argument(std::string("Width of rectangle " + std::to_string(width) + " must be positive"));
    }
    if (height <= 0.0)
    {
      throw std::invalid_argument(std::string("Height of rectangle " + std::to_string(height) + " must be positive"));
    }
  }

  double Rectangle::getWidth() const noexcept
  {
    return figure_.width;
  }

  double Rectangle::getHeight() const noexcept
  {
    return figure_.height;
  }

  point_t Rectangle::getPosition() const noexcept
  {
    return figure_.pos;
  }

  double Rectangle::getArea() const noexcept
  {
    return (figure_.height * figure_.width);
  }

  rectangle_t Rectangle::getFrameRect() const noexcept
  {
    return figure_;
  }

  void Rectangle::setWidth(double width)
  {
    if (width <= 0.0)
    {
      throw std::invalid_argument(std::string("Width of rectangle " + std::to_string(width) + " must be positive"));
    }
    figure_.width = width;
  }

  void Rectangle::setHeight(double height)
  {
    if (height <= 0.0)
    {
      throw std::invalid_argument(std::string("Height of rectangle " + std::to_string(height) + " must be positive"));
    }
    figure_.height = height;
  }

  void Rectangle::move(const point_t& position) noexcept
  {
    figure_.pos = position;
  }

  void Rectangle::move(double x, double y) noexcept
  {
    figure_.pos.x += x;
    figure_.pos.y += y;
  }

  void Rectangle::scale(double coefficient)
  {
    if (coefficient <= 0.0)
    {
      throw std::invalid_argument(std::string("Coefficient of scale" + std::to_string(coefficient) + " must be positive"));
    }
    figure_.width *= coefficient;
    figure_.height *= coefficient;
  }
}