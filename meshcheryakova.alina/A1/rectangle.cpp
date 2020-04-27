#include "rectangle.hpp"
#include <cassert>

Rectangle::Rectangle(double width, double height, const point_t &spot) :
  width_(width),
  height_(height),
  pos_(spot)
{
  assert(width > 0 && height > 0);
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_t{width_, height_, pos_};
}

void Rectangle::move(double x, double y)
{
  pos_.x += x;
  pos_.y += y;
}

void Rectangle::move(const point_t &spot)
{
  pos_ = spot;
}

void Rectangle::printSpot(std::ostream &out)
{
  out << "(" << pos_.x << "," << pos_.y << ")\n";
}

