#include "point.hpp"
#include <iostream>
#include "manipulator.hpp"
#include "flagSaver.hpp"

std::ostream& operator <<(std::ostream& out, const Point& point)
{
  out << "(" << point.x << ";" << point.y << ")";
  return out;
}

std::istream& operator >>(std::istream& in, Point& point)
{
  FlagSaver flagSaver(in);
  in.unsetf(std::ios_base::skipws);
  char symbol = '\0';
  in >> manipulator >> symbol;
  if (symbol != '(')
  {
    in.setstate(std::ios::failbit);
  }
  in >> manipulator >> point.x >> manipulator >> symbol;
  if (symbol != ';')
  {
    in.setstate(std::ios::failbit);
  }  
  in >> manipulator >> point.y >> manipulator >> symbol;
  if (symbol != ')')
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
