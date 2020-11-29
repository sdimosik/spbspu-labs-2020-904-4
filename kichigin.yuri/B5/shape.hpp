#ifndef SHAPE
#define SHAPE
#include <iosfwd>
#include <vector>

struct Point
{
  int x, y;
};

std::istream& operator>>(std::istream& in, Point& point);
void printPointVector(const std::vector<Point>& pointVector, std::ostream& out);

struct Shape
{
  enum FigureType
  {
    TRIANGLE,
    SQUARE,
    RECTANGLE,
    PENTAGON,
    COMMON
  };

  const static size_t MIN_VERTICES = 3u;
  const static size_t TRIANGLE_VERTICES = 3u;
  const static size_t QUADRANGLE_VERTICES = 4u;
  const static size_t PENTAGON_VERTICES = 5u;

  FigureType type;
  std::vector<Point> points;
};

std::istream& operator>>(std::istream& in, Shape& shape);
std::ostream& operator<<(std::ostream& out, const Shape& shape);

bool operator<(const Shape& leftShape, const Shape& rightShape);
bool operator>(const Shape& leftShape, const Shape& rightShape);
bool operator==(const Shape& leftShape, const Shape& rightShape);
bool operator!=(const Shape& leftShape, const Shape& rightShape);
bool operator<=(const Shape& leftShape, const Shape& rightShape);
bool operator>=(const Shape& leftShape, const Shape& rightShape);

#endif // !SHAPE
