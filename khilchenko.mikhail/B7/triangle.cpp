#include "triangle.hpp"

Triangle::Triangle(const Point& point):
    Shape(point)
{}

void Triangle::draw(std::ostream& out) const
{
  out << "TRIANGLE " << center;
}
