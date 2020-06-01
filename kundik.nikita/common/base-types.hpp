#ifndef base_types_hpp
#define base_types_hpp

namespace kundik {
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
#endif
