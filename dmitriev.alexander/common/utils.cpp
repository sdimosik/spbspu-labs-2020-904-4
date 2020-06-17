#include <cmath>
#include "utils.hpp"

double utils::toRadians(double angle)
{
  return angle * M_PI / 180.0;
}

double utils::toDegree(double angle)
{
  return angle * 180.0 / M_PI;
}
