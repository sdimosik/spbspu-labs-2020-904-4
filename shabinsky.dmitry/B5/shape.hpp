#ifndef B5_SHAPE_HPP
#define B5_SHAPE_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cmath>
#include "point.hpp"

struct Shape
{
  enum Type
  {
    TRIANGLE,
    SQUARE,
    RECTANGLE,
    PENTAGON,
    POLYGON
  };
  
  std::vector<Point> points;
  Type type;
};

std::ostream &operator<<(std::ostream &, const Shape &);

std::istream &operator>>(std::istream &, Shape &);

bool operator<(const Shape &, const Shape &);

#endif //B5_SHAPE_HPP
