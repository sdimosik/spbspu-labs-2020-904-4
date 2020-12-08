#include "shapePtr.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "circle.hpp"
#include "square.hpp"
#include "triangle.hpp"

Shape::ShapePtr creatShapePtr(const std::string& name, const Point& center)
{
  if (name == "CIRCLE")
  {
    return std::make_shared<Circle>(center);
  }
  else if (name == "SQUARE")
  {
    return std::make_shared<Square>(center);
  }
  else if (name == "TRIANGLE")
  {
    return std::make_shared<Triangle>(center);
  }
  else
  {
    throw std::invalid_argument("Invalid input in task 2");
  }
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
    shape = creatShapePtr(name, point);
  }
  catch(std::invalid_argument&)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator >>(std::istream& in, Shape::ConstShapePtr& shape)
{
  Shape::ShapePtr temp = std::const_pointer_cast<Shape>(shape);
  in >> temp;
  shape = std::move(temp);
  return in;
}

std::ostream& operator <<(std::ostream& out, const Shape::ShapePtr& shape)
{
  shape->draw(out);
  return out;
}

std::ostream& operator <<(std::ostream& out, const Shape::ConstShapePtr& shape)
{
  out << std::const_pointer_cast<Shape>(shape);
  return out;
}
