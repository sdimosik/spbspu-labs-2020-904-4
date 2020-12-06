#include "point.hpp"
#include <cctype>

std::istream& deleteBlanks(std::istream& in)
{
  while(std::isblank(in.peek()))
  {
    in.ignore();
  }
  return in;
}

std::istream &operator>>(std::istream &in, point_t &point)
{
  if(in.peek() == EOF)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  in >> deleteBlanks;
  if (in.get() != '(')
  {
    in.setstate(std::ios::badbit);
    return in;
  }

  in >> deleteBlanks >> point.x >> deleteBlanks;

  if (in.get() != ';')
  {
    in.setstate(std::ios::badbit);
    return in;
  }

  in >> deleteBlanks >> point.y >> deleteBlanks;

  if (in.get() != ')')
  {
    in.setstate(std::ios::badbit);
    return in;
  }

  return in;
}

std::ostream &operator<<(std::ostream &out, const point_t &point)
{
  return out << " (" << point.x << ";" << point.y << ")";
}
