#ifndef USHAKOV_BASE_TYPES_HPP
#define USHAKOV_BASE_TYPES_HPP

namespace ushakov
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

}
#endif //USHAKOV_BASE_TYPES_HPP
