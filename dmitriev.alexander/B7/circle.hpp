#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(int, int);

  void draw(std::ostream &) const override;
};


#endif
