#ifndef B7_CIRCLE_HPP
#define B7_CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(int, int);
  
  void draw(std::ostream &) const override;
};

#endif //B7_CIRCLE_HPP
