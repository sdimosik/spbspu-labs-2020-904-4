#include "point.hpp"

std::ostream &operator<<(std::ostream &ostream, const Point &point)
{
  ostream << " (" << point.x << ";" << point.y << ")";
  return ostream;
}

std::istream &operator>>(std::istream &in, Point &point)
{
  char check = '\0';
  in.unsetf(std::ios_base::skipws);
  in >> skipSpaces >> check;
  if (in.peek() == EOF)
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  if (check != '(')
  {
    in.setstate(std::ios::failbit);
  }
  in >> skipSpaces >> point.x >> skipSpaces >> check;
  if (check != ';')
  {
    in.setstate(std::ios::failbit);
  }
  
  in >> skipSpaces >>  point.y >> skipSpaces >> check;
  if (check != ')')
  {
    in.setstate(std::ios::failbit);
  }
  
  return in;
}

std::istream &skipSpaces(std::istream &in)
{
  while (std::isblank(in.peek()))
  {
    in.get();
  }
  return in;
}
