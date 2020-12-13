#ifndef SQUARE
#define SQUARE

#include "shape.hpp"

class Square: public Shape
{
public:
  Square(const point_t& point);
  void draw(std::ostream& out) const override;
};

#endif // !SQUARE
