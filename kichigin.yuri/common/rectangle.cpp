#include "rectangle.hpp"
#include <stdexcept>
#include <string>
#include <cmath>

namespace kichigin
{
  Rectangle::Rectangle(double width, double height, const point_t& pos) :
    figure_{ width, height, pos },
    angle_(0)
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
    if (angle_ == 0.0)
    {
      return figure_;
    }
    return rectangle_t{figure_.width * std::abs(std::cos(angle_)) + figure_.height * std::abs(std::sin(angle_)),
        figure_.width * std::abs(std::sin(angle_)) + figure_.height * std::abs(std::cos(angle_)), figure_.pos};
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

  void Rectangle::rotate(double angle) noexcept
  {
    angle -= static_cast<long long>(angle / 360) * 360LL;
    angle_ += angle * M_PI / 180.0;
    if (angle_ > 2.0 * M_PI)
    {
      angle_ -= 2.0 * M_PI;
    }
    else if (angle_ < 2.0 * M_PI)
    {
      angle += 2.0 * M_PI;
    }
  }
}
