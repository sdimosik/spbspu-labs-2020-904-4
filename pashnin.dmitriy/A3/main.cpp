
#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"

int main()
{
  pashnin::point_t dot1{10, 10}, dot2{9, 8}, dot3{2, 0};
  pashnin::Shape *shape = new pashnin::Rectangle(10, 5, dot2);
  std::cout << shape->getArea() << "\n";
  delete shape;
  shape = new pashnin::Circle(3, dot3);
  std::cout << shape->getArea() << "\n";
  delete shape;
  shape = new pashnin::Triangle(dot1, dot2, dot3);
  std::cout << shape->getArea() << "\n";
  delete shape;
  return 0;
}
