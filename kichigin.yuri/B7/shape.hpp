#ifndef SHAPE
#define SHAPE

#include <iosfwd>

struct point_t
{
  int x;
  int y;
};

std::ostream& operator<<(std::ostream& out, const point_t& point);
std::istream& operator>>(std::istream& in, point_t& point);

class Shape
{
public:
  Shape(const point_t& point);
  virtual ~Shape() = default;
  bool isMoreLeft(const Shape& shape) const;
  bool isUpper(const Shape& shape) const;
  virtual void draw(std::ostream& out) const = 0;
protected:
  point_t center_;
};

#endif // !SHAPE
