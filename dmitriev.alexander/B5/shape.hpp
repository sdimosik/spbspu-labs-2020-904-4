#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cmath>
#include "point.hpp"

struct Shape
{
  enum ShapeType
  {
    TRIANGLE,
    SQUARE,
    RECTANGLE,
    PENTAGON,
    POLYGON
  };

  std::vector<Point> points;
  ShapeType type;
};

std::ostream &operator<<(std::ostream &, const Shape &);

std::istream &operator>>(std::istream &, Shape &);

bool operator<(const Shape &, const Shape &);

#endif
