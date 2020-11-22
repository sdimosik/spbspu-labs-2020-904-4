#ifndef B5_TASK2_HPP
#define B5_TASK2_HPP

#include <iterator>
#include <vector>
#include "shape.hpp"

namespace task2
{
  int vertCount;
  int triangleCount;
  int squareCount;
  int rectangleCount;
  
  void collectVerticesCount(std::vector<Shape> &container);
  
  void exec();
  
  void collectVerticesCount(std::vector<Shape> &container)
  {
    std::for_each(container.begin(), container.end(), [&](const Shape &shape) {
      vertCount += shape.points.size();
      
      switch (shape.type)
      {
        case Shape::Type::TRIANGLE:
          triangleCount++;
          break;
        case Shape::Type::SQUARE:
          squareCount++;
          rectangleCount++;
          break;
        case Shape::Type::RECTANGLE:
          rectangleCount++;
          break;
        case Shape::PENTAGON:
        case Shape::POLYGON:
          break;
      }
    });
  }
  
  void exec()
  {
    std::vector<Shape> container{std::istream_iterator<Shape>(std::cin), std::istream_iterator<Shape>()};
    container.erase(std::remove_if(container.begin(), container.end(), [](const Shape &shape) {
      return shape.points.empty();
    }), container.end());
    collectVerticesCount(container);
    
    container.erase(std::remove_if(container.begin(), container.end(), [](const Shape &shape) {
      return shape.type == Shape::Type::PENTAGON;
    }), container.end());
    
    std::vector<Point> points(container.size());
    std::transform(container.begin(), container.end(), points.begin(), [](const Shape &shape) {
      return shape.points.front();
    });
    
    std::sort(container.begin(), container.end());
    
    std::cout << "Vertices: " << vertCount << std::endl;
    std::cout << "Triangles: " << triangleCount << std::endl;
    std::cout << "Squares: " << squareCount << std::endl;
    std::cout << "Rectangles: " << rectangleCount << std::endl;
    std::cout << "Points: ";
    std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(std::cout));
    
    std::cout << std::endl << "Shapes:" << std::endl;
    std::copy(container.begin(), container.end(), std::ostream_iterator<Shape>(std::cout));
  }
}

#endif //B5_TASK2_HPP
