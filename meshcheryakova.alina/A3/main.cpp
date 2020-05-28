#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

int main()
{
  meshcheryakova::Rectangle rectangle(3, 3, {1, 2});
  meshcheryakova::Circle circle({1, 2}, 5);
  meshcheryakova::Shape* shape_rec = &rectangle;
  meshcheryakova::Shape* shape_cir = &circle;
  meshcheryakova::point_t point = {10, 20};
  std::cout << " Area of Rectangle = " << rectangle.getArea() << '\n';
  std::cout << " before scale: " << '\n';
  rectangle.printParametersWithoutSpot(std::cout);
  rectangle.scale(2.0);
  std::cout << " after scale: " << '\n';
  std::cout << " Area of Rectangle a = " << rectangle.getArea() << '\n';
  rectangle.printParametersWithoutSpot(std::cout);
  std::cout << " Area of Circle = " << circle.getArea() << '\n';
  std::cout << " before scale: " << '\n';
  circle.printParametersWithoutSpot(std::cout);
  circle.scale(2.0);
  std::cout << " after scale: " << '\n';
  std::cout << " Area of Circle  = " << circle.getArea() << '\n';
  circle.printParametersWithoutSpot(std::cout);
  std::cout << " Area of Rectangle with shape = " << shape_rec->getArea() << '\n';
  std::cout << " Area of Circle with shape= " << shape_cir->getArea() << '\n';
  std::cout << " FrameRect of Rectangle: height = " <<
  shape_rec->getFrameRect().height << " width = " << shape_rec->getFrameRect().width << '\n';
  std::cout << " FrameRect of Circle: height = " <<
  shape_cir->getFrameRect().height << " width = " << shape_cir->getFrameRect().width << '\n';
  std::cout << " Before move, spot of Rectangle = ";
  shape_rec->printSpot(std::cout);
  std::cout << " Before move, spot of Circle = ";
  shape_cir->printSpot(std::cout);
  shape_rec->move(7, 4);
  shape_cir->move(2, 1);
  std::cout << " After move by x,y " << '\n';
  std::cout << " Rectangle = ";
  shape_rec->printSpot(std::cout);
  std::cout << " Circle = ";
  shape_cir->printSpot(std::cout);
  shape_rec->move(point);
  shape_cir->move(point);
  std::cout << " After move by position " << '\n';
  std::cout << " Rectangle = ";
  shape_rec->printSpot(std::cout);
  std::cout << " Circle = ";
  shape_cir->printSpot(std::cout);
  std::cout << "compositeShape test \n";
  meshcheryakova::CompositeShape array(5);
  meshcheryakova::Rectangle rectangle1(8, 2.5, {7, 0});
  meshcheryakova::Rectangle rectangle2(4, 1.5, {10, 2});
  meshcheryakova::Circle circle1({12, 2}, 3);
  std::shared_ptr<meshcheryakova::Shape> shape1 = std::make_shared<meshcheryakova::Circle>(circle);
  std::shared_ptr<meshcheryakova::Shape> shape2 = std::make_shared<meshcheryakova::Circle>(circle1);
  std::shared_ptr<meshcheryakova::Shape> shape3 = std::make_shared<meshcheryakova::Rectangle>(rectangle);
  std::shared_ptr<meshcheryakova::Shape> shape4 = std::make_shared<meshcheryakova::Rectangle>(rectangle1);
  std::shared_ptr<meshcheryakova::Shape> shape5 = std::make_shared<meshcheryakova::Rectangle>(rectangle2);
  array.addElement(shape1);
  array.addElement(shape2);
  array.addElement(shape3);
  array.addElement(shape4);
  array.addElement(shape5);
  array.printParametersWithoutSpot(std::cout);
  array.deleteElement(2);
  array.deleteElement(3);
  array.printParametersWithoutSpot(std::cout);
  array.scale(2);
  std::cout << " Spot before move = ";
  array.printSpot(std::cout);
  array.move(3,5.5);
  std::cout << " Spot after move = ";
  array.printSpot(std::cout);

  return 0;
}

