#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include <iosfwd>
#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(Point center);
  void draw(std::ostream& out) const override;
};

#endif
