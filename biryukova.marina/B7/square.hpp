#ifndef SQUARE_HPP
#define SQUARE_HPP
#include <iosfwd>
#include "shape.hpp"

class Square : public Shape
{
public:
  Square(Point center);
  void draw(std::ostream& out) const override;
};

#endif
