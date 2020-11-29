#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cmath>

#include "point.hpp"

const size_t TRIANGLE_VERTICES = 3;
const size_t SQUARE_VERTICES = 4;
const size_t PENTAGON_VERTICES = 5;

struct Shape
{
  enum Shapes
  {
    TRIANGLE,
    SQUARE,
    RECTANGLE,
    PENTAGON,
    DEFAULT
  };

  std::vector<Point> points; 
  Shapes shapeType;
};

std::ostream& operator<<(std::ostream& output, const Shape& shape);
std::istream& operator>>(std::istream& input, Shape& shape);
bool operator<(const Shape& left, const Shape& right);
bool isTriangle(const Shape& shape);
bool isSquare(const Shape& shape);
bool isRectangle(const Shape& shape);
bool isPentagon(const Shape& shape);

#endif
