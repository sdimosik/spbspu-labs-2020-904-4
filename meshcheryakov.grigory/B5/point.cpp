#include "point.hpp"
#include "skipSpaces.hpp"
#include <iostream>

std::istream &operator>>(std::istream &in, Point &point)
{
  in.unsetf(std::ios_base::skipws);
  char symbol = '\0';
  in >> skipSpaces >> symbol;
  if (in.peek() == EOF)
  {
    throw std::invalid_argument("Wrong format!\n");
  }

  if (symbol != '(')
  {
    in.setstate(std::ios::failbit);
  }

  in >> skipSpaces >> point.x >> skipSpaces >> symbol;
  if (symbol != ';')
  {
    in.setstate(std::ios::failbit);
  }

  in >> skipSpaces >> point.y >> skipSpaces >> symbol;
  if (symbol != ')')
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::ostream &operator<<(std::ostream &out, const Point &point)
{
  out << "(" << point.x << ";" << point.y << ")";
  return out;
}

