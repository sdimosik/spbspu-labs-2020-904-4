#ifndef TASKS
#define TASKS

#include <string>
#include "shape.hpp"
#include "point.hpp"

void task2();
int countVerticles(const std::vector<Shape>& array);
int countTriangles(const std::vector<Shape>& array);
int countSquares(const std::vector<Shape>& array);
int countRectangles(const std::vector<Shape>& array);
void removePentagons(std::vector<Shape>& array);
void fillPointsVector(const std::vector<Shape>& array, std::vector<Point>& points);

#endif
