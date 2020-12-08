#include <string>
#include <iostream>
#include <stdexcept>

#include "shape.hpp"
#include "geometric-figures.hpp"
#include "blanks.hpp"


Shape::Shape(const Point& point) :
  center_(point)
{}

bool Shape::isMoreLeft(const Shape& shape) const
{
  return this->center_.x < shape.center_.x;
}

bool Shape::isUpper(const Shape& shape) const
{
  return this->center_.y > shape.center_.y;
}

Shape::ShapePtr createShape(const std::string& figureName, const Point& center)
{
  if (figureName == "TRIANGLE")
   {
    return std::make_shared<const Triangle>(center);
   }
   else if (figureName == "SQUARE")
   {
    return std::make_shared<const Square>(center);
   }
   else if (figureName == "CIRCLE")
   {
    return std::make_shared<const Circle>(center);
   }
   else
   {
    throw std::invalid_argument("Invalid input in task 2");
   }
}

std::ostream& operator <<(std::ostream& out, const Shape::ShapePtr& shape)
{
  if (shape)
  {
    shape->draw(out);
  }
  return out;
}

std::istream& operator >>(std::istream& in, Shape::ShapePtr& shape)
{
  std::string name;
  in >> std::ws;
  if (in.peek() == EOF)
  {
    return in;
  }
  while (in.peek() != '(' && !std::isblank(in.peek()))
  {
    if (in.peek() == '\n')
    {
      in.setstate(std::ios::failbit);
      break;
    }
    else
    {
      name += in.get();
    }
  }
  if (in.fail())
  {
    return in;
  }
  Point point;
  in >> point;

  try
  {
    shape = createShape(name, point);
  }
  catch(std::invalid_argument&)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
