#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP
#include <cmath>
struct point_t {
  double x, y;
  bool operator==(const point_t& other) {
    return ((this->x == other.x) && (this->y == other.y));
  }
};

struct rectangle_t {
  double width, height;
  point_t pos;
};
#endif
