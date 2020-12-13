#include "square.hpp"

Square::Square(const Point& point):
    Shape(point)
{}

void Square::draw(std::ostream& out) const
{
  out << "SQUARE " << center;
}
