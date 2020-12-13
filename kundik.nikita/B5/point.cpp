#include "point.hpp"
#include "skipSpaces.hpp"
#include <iostream>

#define WRONF_FORMAT "Wrong format!\n"

std::istream& operator>>(std::istream& in, Point& point)
{
  char symbol = '\0';
  in >> skipSpaces >> symbol;
  if (in.peek() == EOF)
  {
    throw std::invalid_argument("Invalid format!\n");
  }

  if (symbol != '(')
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  in >> skipSpaces >> point.x >> skipSpaces >> symbol;
  if (symbol != ';')
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  in >> skipSpaces >> point.y >> skipSpaces >> symbol;
  if (symbol != ')')
  {
    in.setstate(std::ios_base::failbit);
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const Point& point)
{
  out << "(" << point.x << ";" << point.y << ")";
  return out;
}
