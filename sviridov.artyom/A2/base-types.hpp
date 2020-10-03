#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP
namespace sviridov
{
  struct point_t
  {
    double x;
    double y;
    double getDistance(const point_t&) const;
  };
  struct rectangle_t
  {
    point_t pos;
    double height;
    double width;
    void expandRect(const point_t& pos);
  };
}
#endif
