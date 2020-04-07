#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  Rectangle Rec1(2, 3, {0, 0});
  Circle Cir1({1, 2}, 5);
  Shape* shape_rec = &Rec1;
  Shape* shape_cir = &Cir1;
  point_t point = {10, 20};
  std::cout << " Area of Rectangle = " << Rec1.getArea() << '\n';
  std::cout << " Area of Circle = " << Cir1.getArea() << '\n';
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
