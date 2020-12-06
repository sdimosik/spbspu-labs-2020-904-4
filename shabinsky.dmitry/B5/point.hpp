#ifndef B5_POINT_HPP
#define B5_POINT_HPP

#include <iostream>

struct Point
{
  int x, y;
};

std::ostream &operator<<(std::ostream &, const Point &);

std::istream &operator>>(std::istream &, Point &);

std::istream &skipSpaces(std::istream &in);

#endif //B5_POINT_HPP
