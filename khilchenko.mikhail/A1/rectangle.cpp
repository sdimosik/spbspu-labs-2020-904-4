#include "rectangle.hpp"
#include <stdexcept>
#include <string>

Rectangle::Rectangle(double width, double height, const point_t& pos):
  figure_(rectangle_t{ pos ,width, height})
{
  if (width <= 0.0 || height <= 0)
  {
    throw std::invalid_argument(std::string("Width and height must be positive numbers. Invalid arguments:\nWidth: ")
        + std::to_string(width) + std::string("\nHeight: ") + std::to_string(height));
  }
}

double Rectangle::getArea() const
{
  return (figure_.height * figure_.width);
}

void Rectangle::move(const point_t& newPos)
{
  figure_.pos = newPos;
}

void Rectangle::move(double x, double y)
{
  figure_.pos.x += x;
  figure_.pos.y += y;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_t{ figure_.pos, figure_.width, figure_.height };
}

point_t Rectangle::getCenter() const
{
  return point_t{ figure_.pos.x, figure_.pos.y };
}
