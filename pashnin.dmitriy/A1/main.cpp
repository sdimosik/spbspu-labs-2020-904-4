#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

int main() {
  point_t dot1{10, 10}, dot2{9, 8}, dot3{2, 0};
  Shape *shape = new Rectangle(10, 5, dot2);
  std::cout << shape->getArea() << "\n";
  delete shape;
  shape = new Circle(3, dot3);
  std::cout << shape->getArea() << "\n";
  delete shape;
  shape = new Triangle(dot1, dot2, dot3);
  std::cout << shape->getArea() << "\n";
  delete shape;
  return 0;
}
