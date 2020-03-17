
#include "circle.hpp"
#include <stdexcept>


Circle::Circle(const point_t& pos, double radius) :
  centre_(pos),
  radius_(radius)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("Radius of circle must be positive\n");
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{ radius_ * 2, radius_ * 2, centre_ };
}

void Circle::move(const point_t& point)
{
  centre_ = point;
}

void Circle::move(const double x, const double y)
{
  centre_.x += x;
  centre_.y += y;
}

void Circle::printInfo(std::ostream& out) const
{
  out << "Radius: " << radius_ << '\n'
    << "Center: (" << centre_.x << ", " << centre_.y << ")\n";
}
