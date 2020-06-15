#include "base-types.hpp"

namespace biryukova
{
  bool intersection(const rectangle_t& first, const rectangle_t& second)
  {
    const point_t firstTopLeft = {first.pos.x - (first.width / 2), first.pos.y + (first.height / 2)};
    const point_t firstBottomRight = {first.pos.x + (first.width / 2), first.pos.y - (first.height / 2)};
    const point_t secondTopLeft = {second.pos.x - (second.width / 2), second.pos.y + (second.height / 2)};
    const point_t secondBottomRight = {second.pos.x + (second.width / 2), second.pos.y - (second.height / 2)};
    return !(firstTopLeft.y < secondBottomRight.y || firstBottomRight.y > secondTopLeft.y
        || firstBottomRight.x < secondTopLeft.x || firstTopLeft.x > secondBottomRight.x);
  }
}
