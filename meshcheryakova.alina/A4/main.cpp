#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "Matrix.hpp"

int main()
{
  meshcheryakova::Rectangle rectangle(3, 3, {1, 2});
  meshcheryakova::Circle circle({1, 2}, 5);
  std::cout << "matrix test \n";
  meshcheryakova::CompositeShape array(5);
  meshcheryakova::Rectangle rectangle1(8, 2.5, {7, 0});
  meshcheryakova::Rectangle rectangle2(4, 1.5, {10, 2});
  meshcheryakova::Circle circle1({12, 2}, 3);
  std::shared_ptr<meshcheryakova::Shape> shape1 = std::make_shared<meshcheryakova::Circle>(circle);
  std::shared_ptr<meshcheryakova::Shape> shape2 = std::make_shared<meshcheryakova::Circle>(circle1);
  std::shared_ptr<meshcheryakova::Shape> shape3 = std::make_shared<meshcheryakova::Rectangle>(rectangle);
  std::shared_ptr<meshcheryakova::Shape> shape4 = std::make_shared<meshcheryakova::Rectangle>(rectangle1);
  std::shared_ptr<meshcheryakova::Shape> shape5 = std::make_shared<meshcheryakova::Rectangle>(rectangle2);
  array.addElement(shape2);
  array.addElement(shape4);
  array.addElement(shape5);
  array.addElement(shape4);
  array.addElement(shape5);
  meshcheryakova::Matrix matrix;
  matrix.separate(array);

  for (size_t i = 0; i < matrix.getRows(); i++)
  {
    for (size_t j = 0; j < matrix.getColumns(); j++)
    {
      if(matrix.getShape(i,j) != nullptr)
      {
        std::cout << " Element [" << i << "][" << j << "] Info:\n";
        matrix.getShape(i, j)->printParametersWithoutSpot(std::cout);
      }
    }
  }

  std::cout << "rotate test \n";
  std::cout << "parameters before rotate: \n";
  array.printParametersWithoutSpot(std::cout);
  array.rotate(90);
  std::cout << "parameters after rotate: \n";
  array.printParametersWithoutSpot(std::cout);

  return 0;
}

