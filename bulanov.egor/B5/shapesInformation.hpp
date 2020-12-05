#ifndef B5_SHAPESINFORMATION_HPP
#define B5_SHAPESINFORMATION_HPP

#include "shape.hpp"

class ShapesInformation
{
public:

  ShapesInformation();

  void operator()(Shape &shape);

  friend std::ostream &operator<<(std::ostream &, const ShapesInformation &);

private:
  size_t topsCount_;
  size_t triangleCount_;
  size_t squareCount_;
  size_t rectangleCount_;
};


#endif
