#ifndef SHAPE_COUNTER_HPP
#define SHAPE_COUNTER_HPP

#include <cstddef>
#include "shape.hpp"

class ShapeCounter
{
public:
  ShapeCounter(const std::vector<Shape>&);
  size_t getAmountOfVertices() const noexcept;
  size_t getAmountOfTriangles() const noexcept;
  size_t getAmountOfSquares() const noexcept;
  size_t getAmountOfRectangles() const noexcept;
private:
  size_t amountOfVertices = 0;
  size_t amountOfTriangles = 0;
  size_t amountOfSquares = 0;
  size_t amountOfRectangles = 0;
};

#endif
