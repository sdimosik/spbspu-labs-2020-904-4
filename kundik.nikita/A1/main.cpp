#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  Shape* shape_rec = new Rectangle(point_t{ 3, 4 }, 22, 43);
  std::cout << "Rectangle area = " << shape_rec->getArea() << std::endl;
  delete shape_rec;
  Shape* shape_cir = new Circle(point_t{ 1, 1 }, 10);
  std::cout << "Circle area = " << shape_cir->getArea() << std::endl;
  delete shape_cir;
  Rectangle rectangle(point_t{ 10, 13 }, 2, 8);
  std::cout << "Rectangle area = " << rectangle.getArea() << std::endl;
  std::cout << "Coordinates rectangle center = " << "( " << rectangle.getFrameRect().pos.x << ", " << rectangle.getFrameRect().pos.y << " )" << std::endl;
  return 0;
}
