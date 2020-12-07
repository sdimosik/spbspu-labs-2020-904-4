#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <vector>
#include <iosfwd>
namespace lovkacheva
{
  struct Point
  {
    int x, y;
  };
  
  enum class ShapeType {TRIANGLE, SQUARE, RECTANGLE, OTHER};

  using Shape = std::vector<Point>;
  std::istream& operator>>(std::istream& in, Point& point);
  std::istream& operator>>(std::istream &in, Shape &shape);
  std::ostream& operator<<(std::ostream &out, const Point& point);
  std::ostream& operator<<(std::ostream &out, const Shape& shape);
  ;
  bool compareShapes(const Shape& lhs, const Shape& rhs);
  int squareDistance(const Point& A, const Point& B);
  bool isTriangle(const Shape& shape);
  bool isRectangle(const Shape& shape);
  bool isSquare(const Shape& shape);
  ShapeType getType(const Shape& shape);
}
#endif
