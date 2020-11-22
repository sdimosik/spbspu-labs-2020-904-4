#include "rectangle.hpp"
#include <iostream>
#include <stdexcept>
#include "base-types.hpp"

vasilevskaya::Rectangle::Rectangle(const double height, const double width, const point_t& pos) :
  figure_{ height, width, {pos.x, pos.y} }
{
  if ((width < 0) || (height < 0))
  {
    throw std::invalid_argument("Input error. Enter positive height and width values");
  }
}

double vasilevskaya::Rectangle::getArea() const
{
  return figure_.height * figure_.width;
}

vasilevskaya::point_t vasilevskaya::Rectangle::getPosition() const
{
  return figure_.pos;
}

double vasilevskaya::Rectangle::getHeight() const
{
  return figure_.height;
}

double vasilevskaya::Rectangle::getWidth() const
{
  return figure_.width;
}

vasilevskaya::rectangle_t vasilevskaya::Rectangle::getFrameRect() const
{
  return figure_;
}

void vasilevskaya::Rectangle::move(const double onTheAbscissa, const double onTheOrdinate)
{
  figure_.pos.x += onTheAbscissa;
  figure_.pos.y += onTheOrdinate;
}

void vasilevskaya::Rectangle::move(const point_t& newPoint)
{
  figure_.pos.x = newPoint.x;
  figure_.pos.y = newPoint.y;
}

void vasilevskaya::Rectangle::printFigure() const
{
  std::cout << "This is a rectangle and its bounding rectangle\n" << "Height : " << figure_.height
    << "\nWidth : " << figure_.width
    << "\nCenter : X = " << figure_.pos.x << " Y = " << figure_.pos.y << '\n';
}

void vasilevskaya::Rectangle::printFrameRect() const
{
  std::cout << "height = " << figure_.height << " width = " << figure_.width << " center.x = " << figure_.pos.x << " center.y = "
    << figure_.pos.y << std::endl;
}

void vasilevskaya::Rectangle::scale(double quotient)
{
  if (quotient < 0)
  {
    throw std::invalid_argument("The quotient must be greater or equal than zero");
  }
  figure_.width *= quotient;
  figure_.height *= quotient;
}
