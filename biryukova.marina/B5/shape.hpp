#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <iosfwd>
#include <vector>
#include "point.hpp"

struct Shape
{
  enum ShapeType : size_t
  {
    TRIANGLE,
    SQUARE,
    RECTANGLE,
    OTHER
  };
  std::vector<Point> points;
  ShapeType type;
};

size_t getDistance(const std::pair<int, int>& pair);
int count(int currentSum, const Shape& shape);
bool isTriangle(const Shape& shape);
bool isSquare(const Shape& shape);
bool isRectangle(const Shape& shape);
bool isPentagon(const Shape& shape);
const Point& getFirstPoint(const Shape& shape);
bool comparator(const Shape& lhs, const Shape& rhs);
std::ostream& operator <<(std::ostream& out, const Shape& shape);
std::istream& operator >>(std::istream& in, Shape& shape);

#endif
