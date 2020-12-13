#include "triangle.hpp"
#include <iostream>

Triangle::Triangle(const point_t& point):
  Shape(point)
{}

void Triangle::draw(std::ostream& out) const
{
  out << "TRIANGLE " << center_ << '\n';
}
