#include <iterator>
#include <functional>
#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>
#include "shape.hpp"

namespace tasks
{
  void exec2()
  {
    std::vector<Shape::ShapePtr>
      vector(std::istream_iterator<Shape::ShapePtr>(std::cin),
             std::istream_iterator<Shape::ShapePtr>{});
    
    if ((!std::cin.eof()) && (std::cin.fail()))
    {
      throw std::ios::failure("Task2. Fail while reading data");
    }
    
    std::cout << "Original:" << std::endl;
    std::copy(vector.begin(), vector.end(), std::ostream_iterator<Shape::ShapePtr>(std::cout));
    
    auto lhs = std::bind(&Shape::ShapePtr::operator*, std::placeholders::_1);
    auto rhs = std::bind(&Shape::ShapePtr::operator*, std::placeholders::_2);
    
    std::sort(vector.begin(), vector.end(), std::bind(&Shape::isMoreLeft, lhs, rhs));
    
    std::cout << "Left-Right:" << std::endl;
    std::copy(vector.begin(), vector.end(), std::ostream_iterator<Shape::ShapePtr>(std::cout));
    
    std::reverse(vector.begin(), vector.end());
    std::cout << "Right-Left:" << std::endl;
    std::copy(vector.begin(), vector.end(), std::ostream_iterator<Shape::ShapePtr>(std::cout));
    
    std::sort(vector.begin(), vector.end(), std::bind(&Shape::isUpper, lhs, rhs));
    
    std::cout << "Top-Bottom:" << std::endl;
    std::copy(vector.begin(), vector.end(), std::ostream_iterator<Shape::ShapePtr>(std::cout));
    
    std::reverse(vector.begin(), vector.end());
    std::cout << "Bottom-Top:" << std::endl;
    std::copy(vector.begin(), vector.end(), std::ostream_iterator<Shape::ShapePtr>(std::cout));
  }
}
