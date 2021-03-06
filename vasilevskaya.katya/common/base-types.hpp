#ifndef BASE_TYPES_H
#define BASE_TYPES_H

namespace vasilevskaya
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double height;
    double width;
    point_t pos;
  };
  bool isOverlap(const rectangle_t& firstShape, const rectangle_t& secondShape);
}

#endif
