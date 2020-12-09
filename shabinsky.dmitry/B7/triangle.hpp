#ifndef B7_TRIANGLE_HPP
#define B7_TRIANGLE_HPP

#include "shape.hpp"

class Triangle : public Shape
{
public:
  Triangle(int, int);
  
  void draw(std::ostream &) const override;
};

#endif //B7_TRIANGLE_HPP
