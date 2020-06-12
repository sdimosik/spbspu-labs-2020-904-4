#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP
#include <iostream>

namespace maksimova
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double width;
    double height;
    point_t pos;
    void print() const;
  };
}

#endif
