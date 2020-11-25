#ifndef BASE_TYPES
#define BASE_TYPES

namespace starikevich
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double width, height;
    point_t pos;
  };
}

#endif
