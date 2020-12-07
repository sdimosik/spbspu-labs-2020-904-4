#include "parts.hpp"
#include <algorithm>
#include <deque>
#include <iostream>
#include <numeric>
#include <iterator>
#include <functional>
#include "shape.hpp"
#include "collect-shape-statistics.hpp"
void lovkacheva::partTwo()
{
  std::cin >> std::ws;
  using namespace std::placeholders;
  std::deque<lovkacheva::Shape> shapes;
  std::copy(std::istream_iterator<Shape>(std::cin), std::istream_iterator<Shape>(),
      std::back_inserter(shapes));
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Invalid input");
  }
  lovkacheva::collectShapeStatistics collectShapeStatistics;  
  collectShapeStatistics = std::for_each(shapes.begin(), shapes.end(), collectShapeStatistics);
  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), [](Shape& shape){ return shape.size() == 5; }),
      shapes.end());
  std::vector<Point> points;
  std::transform(shapes.begin(), shapes.end(), std::back_inserter(points), [] (Shape& shape) { return shape[0]; });
  std::sort(shapes.begin(), shapes.end(), lovkacheva::compareShapes);
  std::cout << "Vertices: " << collectShapeStatistics.getVertexNumber() << '\n';
  std::cout << "Triangles: " << collectShapeStatistics.getTriangleNumber() << '\n';
  std::cout << "Squares: " << collectShapeStatistics.getSquareNumber() << '\n';
  std::cout << "Rectangles: " << collectShapeStatistics.getRectangleNumber() << '\n';
  std::cout << "Points: ";
  std::ostream_iterator<lovkacheva::Point> coutPointIt(std::cout, " ");
  std::copy(points.begin(), points.end(), coutPointIt);
  std::cout << "\nShapes:\n";
  std::ostream_iterator<lovkacheva::Shape> coutShapeIt(std::cout, "\n");
  std::copy(shapes.begin(), shapes.end(), coutShapeIt);
}
