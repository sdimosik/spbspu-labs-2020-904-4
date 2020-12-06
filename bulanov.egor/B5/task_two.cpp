#include <functional>
#include <iterator>
#include <algorithm>
#include "shapesInformation.hpp"

void task2()
{
  std::vector<Shape> shapes((std::istream_iterator<Shape>(std::cin)), std::istream_iterator<Shape>());
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::ios_base::failure("Error: there was a problem reading the data!\n");
  }

  ShapesInformation shapeInf;
  std::for_each(shapes.begin(), shapes.end(), std::ref(shapeInf));

  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), [](const Shape &shape)
  {
    return shape.points.size() == 5;
  }), shapes.end());

  std::vector<Point> points(shapes.size());
  std::transform(shapes.begin(), shapes.end(), points.begin(), [](const Shape &shape)
  {
    return shape.points.front();
  });

  std::sort(shapes.begin(), shapes.end());
  std::cout << shapeInf;

  std::cout << "Points: ";
  std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(std::cout));

  std::cout << "\nShapes:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>(std::cout));
}


