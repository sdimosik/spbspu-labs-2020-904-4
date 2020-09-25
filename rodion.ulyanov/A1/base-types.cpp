
#include "base-types.hpp"

bool point_t::operator == (const point_t &other)
{
  return ((this -> x == other.x) && (this -> y == other.y));
}
