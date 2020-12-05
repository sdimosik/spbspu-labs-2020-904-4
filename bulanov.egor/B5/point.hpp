#ifndef B5_POINT_HPP
#define B5_POINT_HPP

#include <iostream>

struct Point
{
  int x;
  int y;
};

std::istream &operator>>(std::istream &, Point &);

std::ostream &operator<<(std::ostream &, const Point &);

#endif
