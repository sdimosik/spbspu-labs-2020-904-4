#include "collect-shape-statistics.hpp"

lovkacheva::collectShapeStatistics::collectShapeStatistics():
  vertexNumber_(0),
  triangleNumber_(0),
  rectangleNumber_(0),
  squareNumber_(0)
{}

void lovkacheva::collectShapeStatistics::operator()(const lovkacheva::Shape& shape)
{
  vertexNumber_ += shape.size();
  if (isTriangle(shape))
  {
    ++triangleNumber_;
    return;
  }
  if (isRectangle(shape))
  {
    ++rectangleNumber_;
  }
  if (isSquare(shape))
  {
    ++squareNumber_;
  }
}

size_t lovkacheva::collectShapeStatistics::getRectangleNumber() const
{
  return rectangleNumber_;
}

size_t lovkacheva::collectShapeStatistics::getTriangleNumber() const
{
  return triangleNumber_;
}

size_t lovkacheva::collectShapeStatistics::getSquareNumber() const
{
  return squareNumber_;
}

size_t lovkacheva::collectShapeStatistics::getVertexNumber() const
{
  return vertexNumber_;
}
