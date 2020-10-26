#ifndef BASE_TYPES_H
#define BASE_TYPES_H

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

#endif
