#include <iostream>
#include <stdexcept>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include "shapePtr.hpp"

void printShapes(const std::vector<Shape::ConstShapePtr>& vector, std::ostream& out)
{
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<Shape::ConstShapePtr>(out, ""));
}

void task2()
{
  std::vector<Shape::ConstShapePtr> vector{std::istream_iterator<Shape::ConstShapePtr>(std::cin), 
      std::istream_iterator<Shape::ConstShapePtr>()};
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error while reading in task 2");
  }
  std::cout << "Original:\n";
  printShapes(vector, std::cout);
  std::cout << "Left-Right:\n";
  std::sort(vector.begin(), vector.end(), std::bind(&Shape::isMoreLeft, std::bind(&Shape::ConstShapePtr::operator*, 
      std::placeholders::_1), std::bind(&Shape::ConstShapePtr::operator*, std::placeholders::_2)));
  printShapes(vector, std::cout);
  std::cout << "Right-Left:\n";
  std::sort(vector.begin(), vector.end(), std::bind(&Shape::isMoreLeft, std::bind(&Shape::ConstShapePtr::operator*, 
      std::placeholders::_2), std::bind(&Shape::ConstShapePtr::operator*, std::placeholders::_1)));
  printShapes(vector, std::cout);
  std::cout << "Top-Bottom:\n";
  std::sort(vector.begin(), vector.end(), std::bind(&Shape::isUpper, std::bind(&Shape::ConstShapePtr::operator*, 
      std::placeholders::_1), std::bind(&Shape::ConstShapePtr::operator*, std::placeholders::_2)));
  printShapes(vector, std::cout);
  std::cout << "Bottom-Top:\n";
  std::sort(vector.begin(), vector.end(), std::bind(&Shape::isUpper, std::bind(&Shape::ConstShapePtr::operator*, 
      std::placeholders::_2), std::bind(&Shape::ConstShapePtr::operator*, std::placeholders::_1)));
  printShapes(vector, std::cout);
}
