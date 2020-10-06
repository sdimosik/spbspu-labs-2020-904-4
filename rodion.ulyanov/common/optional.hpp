#ifndef OPTIONAL_HPP
#define OPTIONAL_HPP
#include "base-types.hpp"
namespace optional
{
  double performToRadians(double angle);

  double performToDegree(double angle);

  double rotate_angle(double source_angle, const double angle);

  double getDistance(const rodion::point_t &point_A, const rodion::point_t &point_B);
}

#endif

