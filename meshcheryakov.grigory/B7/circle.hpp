#ifndef SPBSPU_LABS_2020_904_4_CIRCLE_HPP
#define SPBSPU_LABS_2020_904_4_CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(int, int);

  void draw(std::ostream &) const override;
};

#endif
