#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>
#include <string>
#include <iostream>
#include "point.hpp"

struct Shape
{
  enum class TypeOfShape
  {
    TRIANGLE,
    SQUARE,
    RECTANGLE,
    PENTAGON,
    POLYGON
  };
  std::vector< Point > points;
  TypeOfShape typeOfShape;
};

std::istream& operator>>(std::istream&, Shape&);
std::ostream& operator<<(std::ostream&, const Shape&);

bool isRectangle(const Shape&);
bool isSquare(const Shape&);
bool operator<(const Shape&, const Shape&);

#endif
