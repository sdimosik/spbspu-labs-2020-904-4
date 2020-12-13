#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "shape.hpp"

class Square : public Shape
{
public:
  Square(const Point&);
  void draw(std::ostream&) const override;
};

#endif
