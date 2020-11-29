#ifndef FUNCTiONS_TASK2
#define FUNCTiONS_TASK2
#include <iosfwd>
#include <vector>
#include "shape.hpp"
#include "information.hpp"

Information getInfo(const std::vector<Shape>& shapeVector);
void deletePentagons(std::vector<Shape>& shapeVector);
std::vector<Point> getPointVector(const std::vector<Shape>& shapeVector);
void changeVector(std::vector<Shape>& shapeVector);
void printInfo(const Information& info, std::ostream& out);
void printShapeVector(const std::vector<Shape>& shapeVector, std::ostream& out);

#endif // !FUNCTiONS_TASK2
