#ifndef SPBSPU_LABS_2020_904_4_SQUARE_HPP
#define SPBSPU_LABS_2020_904_4_SQUARE_HPP

#include "shape.hpp"

class Square : public Shape
{
public:
  Square(int, int);

  void draw(std::ostream &) const override;
};

#endif
