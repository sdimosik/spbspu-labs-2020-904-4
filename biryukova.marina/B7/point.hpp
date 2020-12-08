#ifndef POINT_HPP
#define POINT_HPP
#include <iosfwd>

struct Point
{
  int x, y;
};

std::ostream& operator <<(std::ostream& out, const Point& point);
std::istream& operator >>(std::istream& in, Point& point);

#endif
