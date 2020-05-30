#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

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

  return 0;
}

