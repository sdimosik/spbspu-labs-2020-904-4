#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace vorotnikov {
  struct point_t {
    double x, y;
    bool operator==(const point_t &other);
    double getLength(const point_t &other) const;
  };

  struct rectangle_t {
    double width, height;
    point_t pos;
  };
}
#endif
