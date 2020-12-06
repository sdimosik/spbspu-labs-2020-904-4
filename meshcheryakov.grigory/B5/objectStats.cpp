#include "objectStats.hpp"

ObjectStats::ObjectStats() :
    topsCount_(0),
    triangleCount_(0),
    squareCount_(0),
    rectangleCount_(0)
{
}

void ObjectStats::operator()(Shape &shape)
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

std::ostream &operator<<(std::ostream &out, const ObjectStats &objectStats)
{
  out << "Vertices: " << objectStats.topsCount_ << std::endl;
  out << "Triangles: " << objectStats.triangleCount_ << std::endl;
  out << "Squares: " << objectStats.squareCount_ << std::endl;
  out << "Rectangles: " << objectStats.rectangleCount_ << std::endl;
  return out;
}
