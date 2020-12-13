#include "shapeInfo.hpp"

ShapeInfo::ShapeInfo() :
  topsCount_(0),
  triangleCount_(0),
  squareCount_(0),
  rectangleCount_(0)
{
}

void ShapeInfo::operator()(Shape& shape)
{
  if (shape.type == Shape::TRIANGLE)
  {
    ++triangleCount_;
  }
  else if (shape.type == Shape::RECTANGLE)
  {
    ++rectangleCount_;
  }
  else if (shape.type == Shape::SQUARE)
  {
    ++rectangleCount_;
    ++squareCount_;
  }

  topsCount_ += shape.points.size();
}

std::ostream& operator<<(std::ostream& out, const ShapeInfo& objectStats)
{
  out << "Vertices: " << objectStats.topsCount_ << std::endl;
  out << "Triangles: " << objectStats.triangleCount_ << std::endl;
  out << "Squares: " << objectStats.squareCount_ << std::endl;
  out << "Rectangles: " << objectStats.rectangleCount_ << std::endl;
  return out;
}
