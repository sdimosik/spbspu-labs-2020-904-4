#include "rectangle.hpp"
#include <iostream>
#include <cassert>

double Rectangle::getArea() const
{
  return  width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return { pos_, width_, height_ };
}

Rectangle::Rectangle(const point_t& pos, double height, double width) :
   Shape(pos), height_(height), width_(width)
{
  assert(height_ >= 0 && width_ >= 0);
}

void Rectangle::getInform(std::ostream& out) const
{
  out << "Rectangle";
  Shape::getInform(out);
  out << "height = " << height_ << "width = " << width_;
}

std::ostream& operator<<(std::ostream& out, const Rectangle& out_rect)
{
  out_rect.getInform(out);
  return out;
}
