#ifndef B7_SQUARE_HPP
#define B7_SQUARE_HPP

#include "shape.hpp"

class Square : public Shape
{
public:
  Square(int, int);
  
  void draw(std::ostream &) const override;
};

#endif //B7_SQUARE_HPP
