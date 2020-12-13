#ifndef TRIANGLE
#define TRIANGLE

#include "shape.hpp"

class Triangle: public Shape
{
public:
  Triangle(const point_t& point);
  void draw(std::ostream& out) const override;
};

#endif // !TRIANGLE
