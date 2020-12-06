#include "point.hpp"

std::istream &skipSpaces(std::istream &in)
{
  while (std::isblank(in.peek()))
  {
    in.get();
  }
  return in;
}

std::istream &operator>>(std::istream &in, Point &point)
{
  char symbol = '\0';
  in >> skipSpaces >> symbol;

  if (in.peek() == EOF)
  {
    throw std::invalid_argument("Error: there was a problem reading points!\n");
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
  return out << " (" << point.x << ";" << point.y << ')';
}

