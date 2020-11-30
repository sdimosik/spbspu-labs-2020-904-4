#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

struct Point
{
  int x;
  int y;
};

std::ostream &operator<<(std::ostream &, const Point &);
std::istream &operator>>(std::istream &, Point &);

#endif
