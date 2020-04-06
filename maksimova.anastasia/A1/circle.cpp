#include "circle.hpp"
#include <cmath>
#include <stdexcept>

Circle::Circle(double radius, const point_t &pos) :
  radius_(radius),
  center_(pos)
{
  if (radius_ <= 0)
  {
    throw std::invalid_argument("Invalid circle parameters, radius = " + std::to_string(radius));
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {2 * radius_, 2 * radius_, center_};
}

void Circle::move(const point_t &pos)
{
  center_ = pos;
}

void Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::print()
{
  std::cout << "Radius = " << radius_ << "\n"
      << "Center (" << center_.x << ", " << center_.y << ")\n";
}
