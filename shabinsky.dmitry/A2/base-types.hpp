#ifndef HW01_BASE_TYPES_H
#define HW01_BASE_TYPES_H

#include <ostream>

namespace shabinsky
{
  struct point_t
  {
    double x, y;
  };

  struct rectangle_t
  {
    double width, height;
    point_t pos;
  };

  inline std::ostream &operator<<(std::ostream &out, const point_t &point)
  {
    out << "(X: " << point.x << ";Y: " << point.y << ")";
    return out;
  }

  inline std::ostream &operator<<(std::ostream &out, const rectangle_t &rectangle)
  {
    out << "[H: " << rectangle.height << ";W: " << rectangle.width << ";" << rectangle.pos << "]";
    return out;
  }
}
#endif //HW01_BASE_TYPES_H
