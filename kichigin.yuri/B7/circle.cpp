#include "circle.hpp"
#include <iostream>

Circle::Circle(const point_t& point) :
  Shape(point)
{}

void Circle::draw(std::ostream& out) const
{
  out << "CIRCLE " << center_ << '\n';
}
