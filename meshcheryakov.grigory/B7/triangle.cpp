#include "triangle.hpp"

Triangle::Triangle(const int x, const int y) :
    Shape(x, y)
{}

void Triangle::draw(std::ostream &out) const
{
  out << "TRIANGLE (" << x_ << ";" << y_ << ")" << std::endl;
}
