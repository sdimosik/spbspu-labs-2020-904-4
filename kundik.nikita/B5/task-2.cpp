#include "tasks.hpp"
#include <stdexcept>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <numeric>

int countVerticles(const std::vector<Shape>& array)
{
  return std::accumulate(array.begin(), array.end(), 0, count);
}

int countTriangles(const std::vector<Shape>& array)
{
  return std::count_if(array.begin(), array.end(),
    [](const Shape& shape)
    {
      return (shape.type == Shape::TRIANGLE);
    });
}

int countSquares(const std::vector<Shape>& array)
{
  return std::count_if(array.begin(), array.end(),
    [](const Shape& shape)
    {
      return (shape.type == Shape::SQUARE);
    });
}

int countRectangles(const std::vector<Shape>& array)
{
  return std::count_if(array.begin(), array.end(),
    [](const Shape& shape)
    {
      return (shape.type == Shape::SQUARE || shape.type == Shape::RECTANGLE);
    });
}

void removePentagons(std::vector<Shape>& array)
{
  array.erase(std::remove_if(array.begin(), array.end(), isPentagon), array.end());
}

void fillPointsVector(const std::vector<Shape>& array, std::vector<Point>& points)
{
  std::transform(array.begin(), array.end(), points.begin(), getFirstPoint);
}

void task2()
{
  std::vector<Shape> shapes{ std::istream_iterator<Shape>(std::cin), std::istream_iterator<Shape>() };
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error while reading in task 2");
  }
  std::cout << "Vertices: " << countVerticles(shapes) << '\n';
  std::cout << "Triangles: " << countTriangles(shapes) << '\n';
  std::cout << "Squares: " << countSquares(shapes) << '\n';
  std::cout << "Rectangles: " << countRectangles(shapes) << '\n';
  removePentagons(shapes);
  std::vector<Point> points(shapes.size());
  fillPointsVector(shapes, points);
  std::cout << "Points: ";
  std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(std::cout, " "));
  std::cout << '\n';
  std::sort(shapes.begin(), shapes.end(), comparator);
  std::cout << "Shapes:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>(std::cout, "\n"));
}
