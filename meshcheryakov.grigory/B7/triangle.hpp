#ifndef SPBSPU_LABS_2020_904_4_TRIANGLE_HPP
#define SPBSPU_LABS_2020_904_4_TRIANGLE_HPP

#include "shape.hpp"

class Triangle : public Shape
{
public:
  Triangle(int, int);

  void draw(std::ostream &) const override;
};

#endif
