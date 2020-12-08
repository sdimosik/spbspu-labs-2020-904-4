#include "circle.hpp"
#include <iostream>

Circle::Circle(Point center) :
  Shape(center)
{}

void Circle::draw(std::ostream& out) const
{
  out << "CIRCLE " << center_ << "\n";
}
