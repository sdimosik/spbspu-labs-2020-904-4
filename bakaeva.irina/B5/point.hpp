#ifndef B5_POINT_HPP
#define B5_POINT_HPP

#include <iostream>

struct point_t
{
  int x, y;
};

std::istream& deleteBlanks(std::istream& in);

std::istream &operator>>(std::istream &in, point_t &point);

std::ostream &operator<<(std::ostream &out, const point_t &point);

#endif
