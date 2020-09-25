#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

struct point_t
{
  double x, y;
};

struct rectangle_t
{
  double width, height;
  point_t pos;
};

struct triangle_t
{
  double base, sideLeft, sideRight;
  point_t pos;
};

#endif
