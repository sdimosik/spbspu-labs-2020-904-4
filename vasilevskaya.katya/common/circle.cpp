#define _USE_MATH_DEFINES
#include "circle.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>
#include "base-types.hpp"

vasilevskaya::Circle::Circle(const vasilevskaya::point_t& point, const double radius) :
  center_{ point.x, point.y },
  radius_{ radius }
{
  if (radius < 0)
  {
    throw std::invalid_argument("Input error. Enter a positive radius value");
  }
}

double vasilevskaya::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

vasilevskaya::point_t vasilevskaya::Circle::getPosition() const
{
  return center_;
}

double vasilevskaya::Circle::getRadius() const
{
  return radius_;
}

void vasilevskaya::Circle::move(const double onTheAbscissa, const double onTheOrdinate)
{
  center_.x += onTheAbscissa;
  center_.y += onTheOrdinate;
}

void vasilevskaya::Circle::move(const point_t& newPoint)
{
  center_.x = newPoint.x;
  center_.y = newPoint.y;
}

vasilevskaya::rectangle_t vasilevskaya::Circle::getFrameRect() const
{
  return { radius_ * 2, radius_ * 2, center_ };
}

void vasilevskaya::Circle::printFigure() const
{
  std::cout << "it is Circle\n"
    << "Center :  X = " << center_.x << " Y = " << center_.y
    << "\nRadius : " << radius_ << '\n'
    << "\nBounding rectangle for a circle\n"
    << "Height : " << getFrameRect().height
    << "\nWidth : " << getFrameRect().width
    << "\nCenter : X = " << getFrameRect().pos.x << " Y = " << getFrameRect().pos.y << '\n';
}

void vasilevskaya::Circle::printFrameRect() const
{
  rectangle_t rect = getFrameRect();

  std::cout << "height = " << rect.height << " width = " << rect.width << " center.x = " << rect.pos.x
    << " center.y = "
    << rect.pos.y << std::endl;
}

void vasilevskaya::Circle::scale(double quotient)
{
  if (quotient < 0)
  {
    throw std::invalid_argument("The quotient must be greater or equal than zero");
  }
  radius_ *= quotient;
}

void vasilevskaya::Circle::rotate(double)
{}
