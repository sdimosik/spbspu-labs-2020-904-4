#include "rectangle.hpp"
#include <stdexcept>
#include <string>

namespace meshcheryakov
{
  Rectangle::Rectangle(const rectangle_t &rect) :
    rect_(rect)
  {
    if (rect_.width <= 0.0)
    {
      throw std::invalid_argument(std::string("Width must be positive, width = "
          + std::to_string(rect_.width)));
    }
    if (rect_.height <= 0.0)
    {
      throw std::invalid_argument(std::string("Height must be positive, height = "
          + std::to_string(rect_.height)));
    }
  }

  double Rectangle::getArea() const
  {
    return rect_.height * rect_.width;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return rect_;
  }

  void Rectangle::move(double dx, double dy)
  {
    rect_.pos.x += dx;
    rect_.pos.y += dy;
  }

  void Rectangle::move(const point_t &point)
  {
    rect_.pos = point;
  }

  void Rectangle::scale(const double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument(std::string("Coefficient must be positive, coefficient = "
          + std::to_string(coefficient)));
    }
    rect_.width *= coefficient;
    rect_.height *= coefficient;
  }

  point_t Rectangle::getPosition() const
  {
    return rect_.pos;
  }

  double Rectangle::getWidth() const
  {
    return rect_.width;
  }

  double Rectangle::getHeight() const
  {
    return rect_.height;
  }
}
