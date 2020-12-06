#include <iostream>
#include <vector>
#include <iterator>
#include "shape.hpp"
#include "functions-task2.hpp"

void task2()
{
  std::vector<Shape> shapeVector{ std::istream_iterator<Shape>(std::cin),
      std::istream_iterator<Shape>() };
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::invalid_argument("Error in input");
  }

  Information info = getInfo(shapeVector);
  deletePentagons(shapeVector);
  std::vector<Point> pointVector = getPointVector(shapeVector);
  changeVector(shapeVector);
  printInfo(info, std::cout);
  std::cout << "\nPoints:";
  printPointVector(pointVector, std::cout);
  std::cout << "Shapes:\n";
  printShapeVector(shapeVector, std::cout);
}
