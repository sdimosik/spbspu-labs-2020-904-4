#include "rectangle.hpp"
#include <cassert>
#include <iostream>

Rectangle::Rectangle(const point_t& centre, double width, double height) :
  rectangle_(rectangle_t{width, height, centre})
{
  testValidParameters(this->rectangle_);
}

Rectangle::Rectangle(const rectangle_t& rectangle) :
  rectangle_(rectangle)
{
  testValidParameters(this->rectangle_);
}


double Rectangle::getArea() const
{
  return (rectangle_.width * rectangle_.height);
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_;
}

void Rectangle::move(const point_t& centre)
{
  rectangle_.pos = centre;
}

void Rectangle::move(double x, double y)
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
  assert(rectangle.height > 0 && rectangle.width > 0);
}
