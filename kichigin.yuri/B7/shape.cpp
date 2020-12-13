#include "shape.hpp"
#include <iostream>
#include "skip.hpp"
#include "input-guard.hpp"

std::ostream& operator<<(std::ostream& out, const point_t& point)
{
  return out << '(' << point.x << ';' << point.y << ')';
}

std::istream& operator>>(std::istream& in, point_t& point)
{
  InputGuard guard(in);
  in.unsetf(in.skipws);
  int x, y;
  char openBracket = '\0', closeBracket = '\0', delimeter = '\0';
  in >> skipBlanks >> openBracket >> skipBlanks >> x >> skipBlanks >> delimeter 
      >> skipBlanks >> y >> skipBlanks >> closeBracket;
  if (openBracket != '(' || closeBracket != ')' || delimeter != ';' || in.fail())
  {
    in.setstate(in.failbit);
  }
  else
  {
    point.x = x;
    point.y = y;
  }
  return in;
}

Shape::Shape(const point_t& point) :
  center_(point)
{}

bool Shape::isMoreLeft(const Shape& shape) const
{
  return center_.x < shape.center_.x;
}

bool Shape::isUpper(const Shape& shape) const
{
  return center_.y > shape.center_.y;
}
