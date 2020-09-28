#ifndef A4_DETAIL_HPP
#define A4_DETAIL_HPP

#include <cmath>

#include "base-types.hpp"

namespace ushakov
{
  namespace detail
  {
    inline double getDistance(const point_t& point1, const point_t& point2)
    {
      return sqrt((point2.x - point1.x) * (point2.x - point1.x) + (point2.y - point1.y) * (point2.y - point1.y));
    }
  }
}

#endif //A4_DETAIL_HPP
