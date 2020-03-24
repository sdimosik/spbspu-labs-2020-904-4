#include "circle.hpp"
#include <stdexcept>
#include <cmath>

Circle::Circle(double radius, const point_t &position) :
  radius_(radius),
  position_(position)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("Radius must be positive. Radius: " + std::to_string(radius));
  }
}

double Circle::getRadius() const
{
  return radius_;
}

point_t Circle::getPosition() const
{
  return position_;
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{2 * radius_, 2 * radius_, position_};
}

void Circle::move(const point_t &position)
{
  position_ = position;
}

void Circle::move(double x, double y)
{
  position_.x += x;
  position_.y += y;
}

std::ostream &operator<<(std::ostream &out, const Circle &circle)
{
  out << "[R: " << circle.radius_ << ";" << circle.position_ << "]";
  return out;
}
