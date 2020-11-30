#include "statsObject.hpp"

StatsObject::StatsObject() :
  verticesCount_(0),
  triangleCount_(0),
  squareCount_(0),
  rectangleCount_(0)
{
}

void StatsObject::operator()(Shape &shape)
{
  verticesCount_ += shape.points.size();

  switch (shape.type)
  {
    case Shape::ShapeType::TRIANGLE:
      triangleCount_++;
      break;
    case Shape::ShapeType::SQUARE:
      squareCount_++;
      rectangleCount_++;
      break;
    case Shape::ShapeType::RECTANGLE:
      rectangleCount_++;
      break;
    case Shape::PENTAGON:
    case Shape::POLYGON:
      break;
  }
}

std::ostream &operator<<(std::ostream &ostream, const StatsObject &statsObject)
{
  ostream << "Vertices: " << statsObject.verticesCount_ << std::endl;
  ostream << "Triangles: " << statsObject.triangleCount_ << std::endl;
  ostream << "Squares: " << statsObject.squareCount_ << std::endl;
  ostream << "Rectangles: " << statsObject.rectangleCount_ << std::endl;
  return ostream;
}
