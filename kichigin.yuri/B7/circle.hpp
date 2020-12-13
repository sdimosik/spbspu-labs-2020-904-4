#ifndef CIRCLE
#define CIRLE

#include "shape.hpp"

class Circle: public Shape
{
public:
  Circle(const point_t& point);
  void draw(std::ostream& out) const override;
};

#endif // !CIRCLE
