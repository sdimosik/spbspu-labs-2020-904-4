#include "rectangle.hpp"
#include <stdexcept>


Rectangle::Rectangle(const point_t& center, const double width, const double height) :
  rect({ center, width, height })
{
  if (width <= 0 || height <= 0)
  {
    throw std::invalid_argument(" Dimensions can't be negaitve or equal to zero. ");
  }
}

double Rectangle::getArea() const
{
  return (rect.width * rect.height);
}

rectangle_t Rectangle::getFrameRect() const
{
  return rect;
}

void Rectangle::move(const double dx, const double dy)
{
  rect.pos.x += dx;
  rect.pos.y += dy;
}

void Rectangle::move(const point_t& pt)
{
  rect.pos = pt;
}
