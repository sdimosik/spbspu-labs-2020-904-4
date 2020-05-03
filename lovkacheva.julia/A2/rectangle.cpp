#include "rectangle.hpp"

namespace lovkacheva
{
  Rectangle::Rectangle(const rectangle_t& contents) :
    contents_(contents)
  {
    if (contents.width <= 0)
    {
      throw std::invalid_argument(
        "The width of the rectangle must be positive (width = " + std::to_string(contents.width) + ")");
    }
    if (contents.height <= 0)
    {
      throw std::invalid_argument(
        "The height of the rectangle must be positive (height = " + std::to_string(contents.height) + ")");
    }
  }

  void Rectangle::print(std::ostream& out) const
  {
    out << "Rectangle (width = " << contents_.width << "; height = " << contents_.height
        << "; pos(" << contents_.pos.x << ", " << contents_.pos.y << "))";
  }

  double Rectangle::getArea() const
  {
    return (contents_.height * contents_.width);
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return contents_;
  }

  void Rectangle::move(const point_t& newPosition)
  {
    contents_.pos = newPosition;
  }

  void Rectangle::move(double dx, double dy)
  {
    contents_.pos.x += dx;
    contents_.pos.y += dy;
  }

  void Rectangle::scale(double coefficient)
  {
    if (coefficient <= 0.0)
    {
      throw std::invalid_argument(
        "The coefficient must be positive (coefficient = " + std::to_string(coefficient) + ")");
    }
    contents_.width *= coefficient;
    contents_.height *= coefficient;
  }
}
