#include "point.hpp"

std::ostream &operator<<(std::ostream &ostream, const Point &point)
{
  ostream << " (" << point.x << ";" << point.y << ")";
  return ostream;
}

std::istream &operator>>(std::istream &in, Point &point)
{
  if (in.peek() == EOF)
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  in.get() != '(' ? throw std::invalid_argument("bad format data") : 0;
  
  int number;
  in >> number;
  point.x = number;
  in.get() != ';' ? throw std::invalid_argument("bad format data") : 0;

  in >> number;
  point.y = number;
  in.get() != ')' ? throw std::invalid_argument("bad format data") : 0;
  
  return in;
}
