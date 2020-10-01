#define _USE_MATH_DEFINES
#include <cmath>
#include "optional.hpp"

double optional::performToRadians(double angle){
  return angle * M_PI / 180.0;
}

double optional::performToDegree(double angle){
  return angle * 180.0 / M_PI;
}

double optional::rotate_angle(double source_angle, const double angle){
  source_angle += optional::performToRadians(angle);
  const double full_circle = optional::performToRadians(360);
  source_angle = fmod(source_angle, full_circle);
  if (source_angle < 0) {
    source_angle += full_circle;
  }
  return source_angle;
}
