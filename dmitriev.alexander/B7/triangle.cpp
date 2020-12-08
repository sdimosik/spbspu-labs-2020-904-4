#include "triangle.hpp"

Triangle::Triangle(const int x, const int y) :
  Shape(x, y)
{}

void Triangle::draw(std::ostream &ostream) const
{
  ostream << "TRIANGLE (" << x_ << ";" << y_ << ")" << std::endl;
}
