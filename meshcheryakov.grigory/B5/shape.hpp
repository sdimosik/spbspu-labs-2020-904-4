#ifndef SPBSPU_LABS_2020_904_4_SHAPE_HPP
#define SPBSPU_LABS_2020_904_4_SHAPE_HPP

#include "point.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>
#include <cmath>


struct Shape
{
  enum ShapeType
  {
    TRIANGLE,
    SQUARE,
    RECTANGLE,
    OTHER
  };

  std::vector<Point> points;
  ShapeType type;
};

std::istream &operator>>(std::istream &, Shape &);

std::ostream &operator<<(std::ostream &, const Shape &);

bool operator<(const Shape &, const Shape &);

bool isTriangle(const Shape &shape);

bool isRectangle(const Shape &shape);

bool isSquare(const Shape &shape);

#endif
