#include "base-types.hpp"
#include <cmath>

namespace vorotnikov {
  bool point_t::operator==(const point_t &other) {
    return ((this->x == other.x) && (this->y == other.y));
  }

  double point_t::getLength(const point_t &other) const {
    return sqrt(pow(other.x - this->x, 2) + pow(other.y - this->y, 2));
  }
}
