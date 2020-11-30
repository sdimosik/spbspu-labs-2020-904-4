#include "point.hpp"

std::ostream &operator<<(std::ostream &ostream, const Point &point)
{
  ostream << " (" << point.x << ';' << point.y << ')';
  return ostream;
}

std::istream &operator>>(std::istream &in, Point &point)
{
  if (in.peek() == EOF || in.peek() == '\n')
  {
    throw std::invalid_argument("Wrong format!\n");
  }
  in >> std::ws;
  if (in.get() != '(')
  {
    in.setstate(std::ios::failbit);
  }
  int number;
  in >> number >> std::ws;
  point.x = number;
  if (in.get() != ';')
  {
    in.setstate(std::ios::failbit);
  }
  in >> number >> std::ws;
  point.y = number;
  if (in.get() != ')')
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
