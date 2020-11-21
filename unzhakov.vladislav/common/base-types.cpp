#include "base-types.hpp"
#include <cmath>

bool unzhakov::isIntersect(const rectangle_t &rect1, const rectangle_t &rect2)
{
  const bool temp1 = fabs(rect2.pos.x - rect1.pos.x) < ((rect2.width / 2) + (rect1.width / 2));
  const bool temp2 = fabs(rect2.pos.y - rect1.pos.y) < ((rect2.height / 2) + (rect1.height / 2));
  return temp1 && temp2;
}

unzhakov::point_t unzhakov::rotatePoint(const double degrees, const unzhakov::point_t &center, const unzhakov::point_t &point)
{
  const double radians = M_PI * degrees / 180;
  const double cos = std::cos(radians);
  const double sin = std::sin(radians);
  const double newX = center.x + (point.x - center.x) * cos - (point.y - center.y) * sin;
  const double newY = center.y + (point.x - center.x) * sin + (point.y - center.y) * cos;
  return {newX, newY};
}
