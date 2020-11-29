#include "shape.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

void task2()
{
  std::vector<Shape> shapes((std::istream_iterator<Shape>(std::cin)), std::istream_iterator<Shape>());

  std::for_each(std::istream_iterator<Shape>(std::cin), std::istream_iterator<Shape>(), [&](const Shape &newShape)
  {
    shapes.push_back(newShape);
  });


  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Invalid entry of shapes");
  }

  size_t amountOfTriangles = 0;
  size_t amountOfSquares = 0;
  size_t amountOfRectangles = 0;
  size_t tops = 0;

  std::for_each(shapes.begin(), shapes.end(), [&](const Shape& shape)
  {
      tops += shape.points.size();

      if (shape.points.size() == TRIANGLE_VERTICES)
      {
        amountOfTriangles++;
      }

      if (shape.points.size() == SQUARE_VERTICES)
      {
        if (isSquare(shape))
        {
          amountOfSquares++;
        }
        if (isRectangle(shape))
        {
          amountOfRectangles++;
        }
      }
  });

  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), [&](const Shape &shape)
  {
    return shape.points.size() == PENTAGON_VERTICES;
  }), shapes.end());

  std::sort(shapes.begin(), shapes.end());
  std::vector<Point> points;

  std::cout << "Vertices: " << tops << '\n';
  std::cout << "Triangles: " << amountOfTriangles <<'\n';
  std::cout << "Squares: " << amountOfSquares << '\n';
  std::cout << "Rectangles: " << amountOfRectangles << '\n';

  std::cout << "Points: ";
  for (const auto &point : points)
  {
    std::cout << point;
  }
  std::cout << '\n';


  std::cout << "Shapes:\n";
  for (const auto &shape : shapes)
  {
    std::cout << shape.points.size() << " ";
    std::copy(shape.points.begin(), shape.points.end(), std::ostream_iterator<Point>(std::cout));
    std::cout << "\n";
  }

}

