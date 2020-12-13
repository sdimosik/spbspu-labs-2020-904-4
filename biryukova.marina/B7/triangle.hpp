#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include <iosfwd>
#include "shape.hpp"

class Triangle : public Shape
{
public:
  Triangle(Point center);
  void draw(std::ostream& out) const override;
};

#endif
