#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "shape.hpp"
#include "algorithm.hpp"


void task2()
{
  vectorShapes shapes;

  std::for_each(std::istream_iterator<Shape>(std::cin), std::istream_iterator<Shape>(), [&](const Shape &newShape)
  {
    shapes.push_back(newShape);
  });

  if ((!std::cin.eof()) && (std::cin.fail()))
  {
    throw std::invalid_argument("Error by reading data!");
  }

  size_t countOfVertices = 0;
  size_t countOfTriangles = 0;
  size_t countOfSquare = 0;
  size_t countOfRectangle = 0;

  std::for_each(shapes.begin(), shapes.end(), [&](const Shape &shape)
  {
    countOfVertices += shape.points.size();

    if (shape.points.size() == TRIANGLE_VERT)
    {
      countOfTriangles++;
    }

    if (shape.points.size() == QUADRANGLE_VERT)
    {
      if (isSquare(shape))
      {
        countOfSquare++;
      }
      if (isRectangle(shape))
      {
        countOfRectangle++;
      }
    }
  });

  deletePentagon(shapes);

  std::vector<point_t> points = extractPointsFromShapes(shapes);

  std::sort(shapes.begin(), shapes.end());

  std::cout << "Vertices: " << countOfVertices << '\n'
      << "Triangles: " << countOfTriangles << '\n'
      << "Squares: " << countOfSquare << '\n'
      << "Rectangles: " << countOfRectangle << '\n';

  std::cout << "Points:";
  for (const auto &point : points)
  {
    std::cout << point;
  }
  std::cout << '\n';

  std::cout << "Shapes:\n";
  for (const auto &shape : shapes)
  {
    std::cout << shape.points.size() << " ";
    std::copy(shape.points.begin(), shape.points.end(), std::ostream_iterator<point_t>(std::cout));
    std::cout << "\n";
  }
}
