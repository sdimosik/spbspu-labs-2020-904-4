#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const point_t& pos, double width, double height) :
  rectangle_{ width, height, pos }
{
  if (width <= 0)
  {
    throw std::invalid_argument("The width of the rectangle must be a positive number.");
  }
  if (height <= 0)
  {
    throw std::invalid_argument("The height of the rectangle must be a positive number.");
  }
}

void Rectangle::move(const point_t& pos)
{
  rectangle_.pos = pos;
}

void Rectangle::move(double x, double y)
{
  rectangle_.pos.x += x;
  rectangle_.pos.y += y;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_;
}

double Rectangle::getWidth() const
{
  return rectangle_.width;
}

double Rectangle::getHeight() const
{
  return rectangle_.height;
}

void Rectangle::setWidth(double width)
{
  if (width <= 0)
  {
    throw std::invalid_argument("The width of the rectangle must be a positive number.");
  }
  rectangle_.width = width;
}

void Rectangle::setHeight(double height)
{
  if (height <= 0)
  {
    throw std::invalid_argument("The height of the rectangle must be a positive number.");
  }
  rectangle_.height = height;
}

point_t Rectangle::getPosition() const
{
  return rectangle_.pos;
}

double Rectangle::getArea() const
{
  return (rectangle_.width * rectangle_.height);
}
