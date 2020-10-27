#define _USE_MATH_DEFINES
#include "circle.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>
#include "base-types.hpp"

 Circle::Circle(const point_t& point, const double radius) :
  center_{ point.x, point.y },
  radius_{ radius }
{
  if (radius < 0)
  {
    throw std::invalid_argument("Input error. Enter a positive radius value");
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

void Circle::move(const double onTheAbscissa, const double onTheOrdinate)
{
  center_.x += onTheAbscissa;
  center_.y += onTheOrdinate;
}

void Circle::move(const point_t& newPoint)
{
  center_.x = newPoint.x;
  center_.y = newPoint.y;
}

rectangle_t Circle::getFrameRect() const
{
  return { radius_ * 2, radius_ * 2, center_ };
}

void Circle::printFigure() const
{
  std::cout << "it is Circle\n"
    << "Center :  X = " << center_.x << " Y = " << center_.y
    << "\nRadius : " << radius_ << '\n'
    << "\nBounding rectangle for a circle\n"
    << "Height : " << getFrameRect().height
    << "\nWidth : " << getFrameRect().width
    << "\nCenter : X = " << getFrameRect().pos.x << " Y = " << getFrameRect().pos.y << '\n';
}
