#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP
namespace bulanov
{
  struct point_t
  {
    double x, y;
  };

  struct rectangle_t
  {
    double width, height;
    point_t pos;
  };
}

#endif
