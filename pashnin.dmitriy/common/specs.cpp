
#include <cmath>
#include "specs.hpp"

double specs::toRadians(double angle)
{
  return angle * M_PI / 180.0;
}

double specs::toDegree(double angle)
{
  return angle * 180.0 / M_PI;
}

double specs::changeAngle(double sourceAngle, double angle)
{
  sourceAngle += specs::toRadians(angle);
  const double fullCircle = 2 * M_PI;
  sourceAngle = fmod(sourceAngle, fullCircle);
  if (sourceAngle < 0)
  {
    sourceAngle += fullCircle;
  }
  return sourceAngle;
}
