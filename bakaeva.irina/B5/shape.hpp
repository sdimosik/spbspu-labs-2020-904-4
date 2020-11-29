#ifndef SPBSPU_LABS_2020_904_4_SHAPE_HPP
#define SPBSPU_LABS_2020_904_4_SHAPE_HPP

#include <iostream>
#include <vector>
#include "point.hpp"

const size_t MIN_COUNT_OF_POINTS = 3;
const size_t TRIANGLE_VERT = 3;
const size_t QUADRANGLE_VERT = 4;
const size_t PENTAGON_VERT = 5;

struct Shape
{
  enum ShapeType
  {
    TRIANGLE,
    SQUARE,
    RECTANGLE,
    PENTAGON,
    OTHER
  };

  ShapeType type;
  std::vector<point_t> points;
};

using vectorShapes = std::vector<Shape>;

std::istream &operator>>(std::istream &in, Shape &shape);

bool operator<(const Shape &shape1, const Shape &shape2);

bool isRectangle(const Shape &shape);

bool isSquare(const Shape &shape);

int getSideLength(const point_t &point1, const point_t &point2);

#endif
