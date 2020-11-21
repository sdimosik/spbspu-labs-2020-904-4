#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP
namespace unzhakov
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


  bool isIntersect(const rectangle_t &rect1, const rectangle_t &rect2);

  point_t rotatePoint(double degrees, const point_t &center, const point_t &point);
}
#endif
