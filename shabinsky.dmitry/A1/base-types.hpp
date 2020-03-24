#ifndef HW01_BASE_TYPES_H
#define HW01_BASE_TYPES_H
#include <ostream>

struct point_t
{
  double x, y;
  
  inline friend std::ostream &operator<<(std::ostream &out, const point_t &point);
};

std::ostream &operator<<(std::ostream &out, const point_t &point)
{
  out << "(X: " << point.x << ";Y: " << point.y << ")";
  return out;
}

struct rectangle_t
{
  double width, height;
  point_t pos;
  
  inline friend std::ostream &operator<<(std::ostream &out, const rectangle_t &rectangle);
};

std::ostream &operator<<(std::ostream &out, const rectangle_t &rectangle)
{
  out << "[H: " << rectangle.height << ";W: " << rectangle.width << ";" << rectangle.pos << "]";
  return out;
}

#endif //HW01_BASE_TYPES_H
