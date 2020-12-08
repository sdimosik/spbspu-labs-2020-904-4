#include "triangle.hpp"
#include <iostream>

Triangle::Triangle(Point center) :
  Shape(center)
{}

void Triangle::draw(std::ostream& out) const
{
  out << "TRIANGLE " << center_ << '\n';
}
