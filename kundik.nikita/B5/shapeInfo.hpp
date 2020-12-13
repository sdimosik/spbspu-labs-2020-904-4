#ifndef SHAPE_INFO
#define SHAPE_INFO

#include "shape.hpp"

class ShapeInfo
{
public:
  ShapeInfo();
  void operator()(Shape&);
  friend std::ostream& operator<<(std::ostream&, const ShapeInfo&);
private:
  size_t topsCount_;
  size_t triangleCount_;
  size_t squareCount_;
  size_t rectangleCount_;
};

#endif
