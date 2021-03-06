#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace biryukova
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
  };

  bool intersection(const rectangle_t& first, const rectangle_t& second);
}

#endif
