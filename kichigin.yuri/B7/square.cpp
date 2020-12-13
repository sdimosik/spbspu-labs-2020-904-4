#include "square.hpp"
#include <iostream>

Square::Square(const point_t& point):
  Shape(point)
{}

void Square::draw(std::ostream& out) const
{
  out << "SQUARE " << center_ << '\n';
}
