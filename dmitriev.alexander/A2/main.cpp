#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  dmitriev::Shape *shape1 = new dmitriev::Rectangle(dmitriev::point_t{0, 0}, 2, 4);
  std::cout << shape1->getArea() << "\n";
  delete shape1;
  dmitriev::Shape *shape2 = new dmitriev::Circle(dmitriev::point_t{0, 0}, 4);
  std::cout << shape2->getArea() << "\n";
  delete shape2;
  dmitriev::Rectangle rect(dmitriev::point_t{1, 1}, 4, 2);
  std::cout << rect.getArea() << "\n";

  return 0;
}
