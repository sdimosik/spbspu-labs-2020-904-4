#ifndef POINT
#define POINT

#include <iostream>
#include <iosfwd>

struct Point
{
  int x, y;
};

std::istream& operator>>(std::istream&, Point&);
std::ostream& operator<<(std::ostream&, const Point&);

#endif
