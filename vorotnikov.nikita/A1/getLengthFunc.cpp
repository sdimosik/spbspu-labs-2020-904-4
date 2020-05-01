//
// Created by koliksto on 01.05.2020.
//

#include <cmath>
#include "getLengthFunc.h"

double getLength(point_t point_one, point_t point_two) {
  return sqrt(pow( point_two.x - point_one.x, 2) + pow(point_two.y - point_one.y, 2));
}
