#include "base-types.hpp"
#include <cmath>
#include <stdexcept>

bool vasilevskaya::isOverlap(const vasilevskaya::rectangle_t& firstShape, const vasilevskaya::rectangle_t& secondShape)
{
  if ((firstShape.height == -1) && (secondShape.width == -1))
  {
    return false;
  }
  if ((firstShape.height == -1) && (secondShape.width == -1))
  {
    return false;
  }

  double differenceX = std::abs(firstShape.pos.x - secondShape.pos.x);
  double differenceY = std::abs(firstShape.pos.y - secondShape.pos.y);
  double halfAmountHeight = (firstShape.height + secondShape.height) / 2;
  double halfAmountWidth = (firstShape.width + secondShape.width) / 2;

  return (differenceY < halfAmountHeight) && (differenceX < halfAmountWidth);
}
