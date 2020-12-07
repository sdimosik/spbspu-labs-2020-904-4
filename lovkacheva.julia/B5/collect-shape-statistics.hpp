#ifndef COLLECT_SHAPE_STATISTICS
#define COLLECT_SHAPE_STATISTIC
#include "shape.hpp"
namespace lovkacheva
{
  class collectShapeStatistics
  {
  public:
    collectShapeStatistics();
    void operator()(const Shape& shape);
    size_t getTriangleNumber() const;
    size_t getRectangleNumber() const;
    size_t getSquareNumber() const;
    size_t getVertexNumber() const;
  private:
    size_t vertexNumber_;
    size_t triangleNumber_;
    size_t rectangleNumber_;
    size_t squareNumber_;
  };
}
#endif
