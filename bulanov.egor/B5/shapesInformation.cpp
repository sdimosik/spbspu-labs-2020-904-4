#include "shapesInformation.hpp"

ShapesInformation::ShapesInformation() :
    topsCount_(0),
    triangleCount_(0),
    squareCount_(0),
    rectangleCount_(0)
{
}

void ShapesInformation::operator()(Shape &shape)
{
  topsCount_ += shape.points.size();

  switch (shape.type)
  {
    case Shape::TypeOfShape ::TRIANGLE:
      triangleCount_++;
      break;
    case Shape::TypeOfShape::SQUARE:
      squareCount_++;
      rectangleCount_++;
      break;
    case Shape::TypeOfShape::RECTANGLE:
      rectangleCount_++;
      break;
    case Shape::OTHER:
      break;
  }
}

std::ostream &operator<<(std::ostream &out, const ShapesInformation &shapeInf)
{
  out << "Vertices: " << shapeInf.topsCount_ << std::endl;
  out << "Triangles: " << shapeInf.triangleCount_ << std::endl;
  out << "Squares: " << shapeInf.squareCount_ << std::endl;
  out << "Rectangles: " << shapeInf.rectangleCount_ << std::endl;
  return out;
}

