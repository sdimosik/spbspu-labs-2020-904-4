#include "rectangle.hpp"
#include <stdexcept>
#include <string>

Rectangle::Rectangle(double width, double height, const point_t& pos) :
  figure_{width, height, pos}
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

double Rectangle::getWidth() const
{
  return figure_.width;
}

double Rectangle::getHeight() const
{
  return figure_.height;
}

point_t Rectangle::getPosition() const
{
  return figure_.pos;
}

double Rectangle::getArea() const
{
  return (figure_.height * figure_.width);
}

rectangle_t Rectangle::getFrameRect() const
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

void Rectangle::move(const point_t& position)
{
  figure_.pos = position;
}

void Rectangle::move(double x, double y)
{
  figure_.pos.x += x;
  figure_.pos.y += y;
}
