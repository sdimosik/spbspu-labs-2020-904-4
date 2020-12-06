#include "functions-task2.hpp"
#include <iostream>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <iterator>
#include "checks.hpp"

Information getInfo(const std::vector<Shape>& shapeVector)
{
  Information info{ 0,0,0,0 };
  std::for_each(shapeVector.begin(), shapeVector.end(), [&info](const Shape& shape)
    {
      info.vertices += shape.points.size();

      switch (shape.type)
      {
      case Shape::TRIANGLE:
        ++info.triangles;
        break;
      case Shape::SQUARE:
        ++info.squares;
      case Shape::RECTANGLE:
        ++info.rectangles;
        break;
      default:
        break;
      }
    });
  return info;
}

void deletePentagons(std::vector<Shape>& shapeVector)
{
  shapeVector.erase(std::remove_if(shapeVector.begin(), shapeVector.end(), [](const Shape& shape) -> bool
    {
      return shape.type == Shape::PENTAGON;
    }), shapeVector.end());
}

std::vector<Point> getPointVector(const std::vector<Shape>& shapeVector)
{
  std::vector<Point> pointVector(shapeVector.size());
  std::transform(shapeVector.begin(), shapeVector.end(), pointVector.begin(), [](const Shape& shape) -> Point
    {
      return shape.points[0];
    });
  return pointVector;
}

void changeVector(std::vector<Shape>& shapeVector)
{
  std::sort(shapeVector.begin(), shapeVector.end(), [](const Shape& shapeLeft, const Shape& shapeRight) -> bool
      {
        return shapeLeft < shapeRight;
      });
}

void printInfo(const Information& info, std::ostream& out)
{
  out << "Vertices: " << info.vertices
      << "\nTriangles: " << info.triangles
      << "\nSquares: " << info.squares
      << "\nRectangles: " << info.rectangles;
}

void printShapeVector(const std::vector<Shape>& shapeVector, std::ostream& out)
{
  std::copy(shapeVector.begin(), shapeVector.end(), std::ostream_iterator<Shape>(out));
}
