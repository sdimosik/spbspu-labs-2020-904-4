#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP
namespace sviridov
{
  bool isClose(double, double);
  struct point_t
  {
    double x;
    double y;
    double getDistance(const point_t&) const;
  };

  bool operator==(const point_t &, const point_t &);
  bool operator!=(const point_t &, const point_t &);
  struct rectangle_t
  {
    point_t pos;
    double height;
    double width;
    void expandRect(const point_t& pos);
  };
  bool operator==(const rectangle_t &, const rectangle_t &);
  bool operator!=(const rectangle_t &, const rectangle_t &);
}
#endif
