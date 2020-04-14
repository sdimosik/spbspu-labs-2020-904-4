#include "circle.hpp"
#include <cmath>
#include <cassert>

Circle::Circle(const point_t &pos, const double radius) :
  pos_(pos),
  radius_(radius)
{
  assert(radius > 0);
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{radius_ * 2, radius_ * 2, pos_};
}

void Circle::move(double x, double y)
{
  pos_.x += x;
  pos_.y += y;
}

void Circle::move(const point_t &spot)
{
  pos_ = spot;
}

void Circle::printSpot(std::ostream &out)
{
  out << "(" << pos_.x << "," << pos_.y << ")\n";
}
