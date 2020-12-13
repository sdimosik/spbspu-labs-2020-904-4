#ifndef SHAPE
#define SHAPE

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

std::istream& operator>>(std::istream&, Shape&);
std::ostream& operator<<(std::ostream&, const Shape&);

bool isTriangle(const Shape& shape);
bool isRectangle(const Shape& shape);
bool isSquare(const Shape& shape);

bool operator<(const Shape&, const Shape&);

int count(int currentSum, const Shape& shape);
bool isPentagon(const Shape& shape);
const Point& getFirstPoint(const Shape& shape);
bool comparator(const Shape& lhs, const Shape& rhs);

#endif
