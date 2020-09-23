#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "matrix.hpp"
#include "composite-shape.hpp"

int main()
{
  dmitriev::Rectangle rectangle({0, 0}, 2, 4);
  dmitriev::Circle circle({0, 0}, 5);
  rectangle.rotate(15);
  dmitriev::CompositeShape compositeShape(2);
  std::shared_ptr<dmitriev::Shape> shape1 = std::make_shared<dmitriev::Rectangle>(rectangle);
  compositeShape.addShape(shape1);
  std::shared_ptr<dmitriev::Shape> shape2 = std::make_shared<dmitriev::Circle>(circle);
  compositeShape.addShape(shape2);
  std::cout << compositeShape.getArea() << "\n";
  compositeShape.scale(2);
  std::cout << compositeShape.getArea() << "\n";
  dmitriev::Matrix matrix;
  matrix.addShape(shape1);
  matrix.addShape(shape2);
  compositeShape.rotate(-1000);
  return 0;
}
