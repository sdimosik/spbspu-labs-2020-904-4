#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

struct Point
{
  double x, y;
};

std::istream& operator>>(std::istream&, Point&);
std::ostream& operator<<(std::ostream&, const Point&);

#endif
