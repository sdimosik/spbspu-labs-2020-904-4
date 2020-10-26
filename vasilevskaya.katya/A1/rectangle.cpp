#include "rectangle.hpp"
#include <iostream>
#include <stdexcept>
#include "base-types.hpp"

Rectangle::Rectangle(const double height, const double width, const point_t& pos) :
  figure_{ height, width, {pos.x, pos.y} }
{
  if ((width < 0) || (height < 0))
  {
    throw std::invalid_argument("Input error. Enter positive height and width values");
  }
}

double Rectangle::getArea() const
{
  std::cout << "The area of the rectangle is : ";
  return figure_.height * figure_.width;

}

rectangle_t Rectangle::getFrameRect() const
{
  return figure_;
}

void Rectangle::move(const double onTheAbscissa, const double onTheOrdinate)
{
  figure_.pos.x += onTheAbscissa;
  figure_.pos.y += onTheOrdinate;
}

void Rectangle::move(const point_t& newPoint)
{
  figure_.pos.x = newPoint.x;
  figure_.pos.y = newPoint.y;
}

void Rectangle::printFigure() const
{
  std::cout << "This is a rectangle and its bounding rectangle\n" << "Height : " << figure_.height
    << "\nWidth : " << figure_.width
    << "\nCenter : X = " << figure_.pos.x << " Y = " << figure_.pos.y << '\n';
}
