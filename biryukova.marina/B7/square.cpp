#include "square.hpp"
#include <iostream>

Square::Square(Point center) :
  Shape(center)
{}

void Square::draw(std::ostream& out) const
{
  out << "SQUARE " << center_ << "\n";
}
