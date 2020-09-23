#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  try 
  {
    kundik::Shape* shape_rec = new kundik::Rectangle(kundik::point_t{ 3, 4 }, 22, 43);
    std::cout << "Rectangle area = " << shape_rec->getArea() << std::endl;
    delete shape_rec;
    kundik::Shape* shape_cir = new kundik::Circle(kundik::point_t{ 1, 1 }, 10);
    std::cout << "Circle area = " << shape_cir->getArea() << std::endl;
    delete shape_cir;
    kundik::Rectangle rectangle(kundik::point_t{ 10, 13 }, -2, 8);
    std::cout << "Rectangle area = " << rectangle.getArea() << std::endl;
    std::cout << "Coordinates rectangle center = " << "( " << rectangle.getFrameRect().pos.x << ", " << rectangle.getFrameRect().pos.y << " )" << std::endl;
  }
  catch (std::exception& p) {
    std::cerr << p.what() << std::endl;
  }
 
  catch (...) {
    std::cerr << "Unknown Error" << std::endl;
  }
  return 0;
}
