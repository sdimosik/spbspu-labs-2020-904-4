#ifndef B5_SHAPE_HPP
#define B5_SHAPE_HPP

#include <iostream>
#include <vector>


#include "point.hpp"

struct Shape
{
  enum TypeOfShape
  {
    TRIANGLE,
    SQUARE,
    RECTANGLE,
    OTHER
  };

  std::vector<Point> points;
  TypeOfShape type;
};

std::istream &operator>>(std::istream &, Shape &);

std::ostream &operator<<(std::ostream &, const Shape &);

bool operator<(const Shape &, const Shape &);

#endif
