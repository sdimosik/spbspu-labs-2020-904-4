#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  Shape *shape1 = new Rectangle(point_t{0, 0}, 2, 4);
  std::cout << shape1->getArea() << "\n";
  delete shape1;
  Shape *shape2 = new Circle(point_t{0, 0}, 4);
  std::cout << shape2->getArea() << "\n";
  delete shape2;
  Rectangle rect(point_t{1, 1}, 4, 2);
  std::cout << rect.getArea() << "\n";
}
