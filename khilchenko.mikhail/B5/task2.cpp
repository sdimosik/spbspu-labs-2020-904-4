#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>

#include "shape.hpp"
#include "shapeCounter.hpp"

void task2()
{
  std::vector<Shape> shapes(std::istream_iterator<Shape>(std::cin), std::istream_iterator<Shape>());

  if(!std::cin.eof() && std::cin.fail())
  {
    throw std::runtime_error("Error in reading data in task2");
  }
  ShapeCounter shapeCounter(shapes);
  std::cout << "Vertices: " << shapeCounter.getAmountOfVertices() << '\n';
  std::cout << "Triangles: " << shapeCounter.getAmountOfTriangles() << '\n';
  std::cout << "Squares: " << shapeCounter.getAmountOfSquares() << '\n';
  std::cout << "Rectangles: " << shapeCounter.getAmountOfRectangles() << '\n';

  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), [](const Shape& shape)
      {
        return shape.typeOfShape == Shape::TypeOfShape::PENTAGON;
      }), shapes.end());

  std::vector<Point> points;
  std::for_each(shapes.begin(), shapes.end(), [&points](const Shape& shape){points.push_back(shape.points.at(0));});

  std::cout << "Points: ";
  std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(std::cout, " "));
  std::cout << '\n';
  std::cout << "Shapes:\n";
  std::sort(shapes.begin(), shapes.end());
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>(std::cout, "\n"));
}
