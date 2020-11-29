#ifndef SPBSPU_LABS_2020_904_4_POINT_HPP
#define SPBSPU_LABS_2020_904_4_POINT_HPP

#include <iostream>
#include <iosfwd>

struct Point
{
  int x, y;
};

std::istream &operator>>(std::istream &, Point &);
std::ostream &operator<<(std::ostream &, const Point &);

#endif
