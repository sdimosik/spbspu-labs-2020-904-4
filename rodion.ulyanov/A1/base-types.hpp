
#ifndef base_types_h
#define base_types_h

struct point_t
{
  double x;
  double y;
  bool operator < (const point_t &other);
  bool operator > (const point_t &other);
  bool operator == (const point_t &other);
};

struct rectangle_t
{
  double width;
  double height;
  point_t pos;
};
#endif /* base_types_h */
