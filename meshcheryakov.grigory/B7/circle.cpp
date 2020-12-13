#include "circle.hpp"

Circle::Circle(const int x, const int y) :
    Shape(x, y)
{}

void Circle::draw(std::ostream &out) const
{
  out << "CIRCLE (" << x_ << ";" << y_ << ")" << std::endl;
}
