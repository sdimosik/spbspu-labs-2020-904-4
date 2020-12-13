#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const Point&);
  void draw(std::ostream&) const override;
};

#endif
