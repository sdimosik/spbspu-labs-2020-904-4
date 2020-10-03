#include "base-types.hpp"
#include <cmath>
namespace sviridov
{
  void rectangle_t::expandRect(const point_t &posit)
  {
    if ((posit.y > pos.y + width / 2) || (posit.y < pos.y - width / 2))
    {
      pos.y = posit.y + ((width / 2 + fabs(posit.y - pos.y)) / 2) * ((pos.y - posit.y < 0) ? -1 : 1);
      width = fabs(posit.y - pos.y) * 2;
    }
    if ((posit.x > pos.x + height / 2) || (posit.x < pos.x - height / 2))
    {
      pos.x = posit.x + ((height / 2 + fabs(posit.x - pos.x)) / 2) * ((pos.x - posit.x < 0) ? -1 : 1);
      height = fabs(posit.x - pos.x) * 2;
    }
  }

  double point_t::getDistance(const point_t &posit) const
  {
    return sqrt((posit.x - x) * (posit.x - x) + (posit.y - y) * (posit.y - y));
  }
}
