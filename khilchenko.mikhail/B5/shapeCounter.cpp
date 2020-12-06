#include "shapeCounter.hpp"
#include <numeric>
#include <iterator>

ShapeCounter::ShapeCounter(const std::vector<Shape>& shapes)
{
  amountOfVertices = std::accumulate(shapes.begin(), shapes.end(), 0,
      [](int init, const Shape& shape)
      {
        return init + shape.points.size();
      });
  amountOfTriangles = std::accumulate(shapes.begin(), shapes.end(), 0,
      [](int init, const Shape& shape)
      {
        if(shape.typeOfShape == Shape::TypeOfShape::TRIANGLE)
        {
          return init + 1;
        }
        return init;
      });
  amountOfSquares = std::accumulate(shapes.begin(), shapes.end(), 0,
      [](int init, const Shape& shape)
      {
        if(shape.typeOfShape == Shape::TypeOfShape::SQUARE)
        {
          return init + 1;
        }
        return init;
      });
  amountOfRectangles = std::accumulate(shapes.begin(), shapes.end(), 0,
      [](int init, const Shape& shape)
      {
        if(shape.typeOfShape == Shape::TypeOfShape::RECTANGLE || shape.typeOfShape == Shape::TypeOfShape::SQUARE)
        {
          return init + 1;
        }
        return init;
      });
}

size_t ShapeCounter::getAmountOfVertices() const noexcept
{
  return amountOfVertices;
}

size_t ShapeCounter::getAmountOfTriangles() const noexcept
{
  return amountOfTriangles;
}

size_t ShapeCounter::getAmountOfSquares() const noexcept
{
  return amountOfSquares;
}

size_t ShapeCounter::getAmountOfRectangles() const noexcept
{
  return amountOfRectangles;
}
