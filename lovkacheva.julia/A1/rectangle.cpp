#include "rectangle.hpp"
#include <cassert>

Rectangle::Rectangle(rectangle_t contents):
  contents_(contents)
{
  assert((contents.width > 0) && (contents.height > 0));
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
