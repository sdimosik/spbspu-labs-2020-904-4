#include "geometric-figures.hpp"

void Circle::draw(std::ostream& out) const
{
  out << "CIRCLE " << center_<< '\n';
}

void Triangle::draw(std::ostream& out) const
{
  out << "TRIANGLE " << center_<< '\n';
}

void Square::draw(std::ostream& out) const
{
  out << "SQUARE " << center_<< '\n';
}
