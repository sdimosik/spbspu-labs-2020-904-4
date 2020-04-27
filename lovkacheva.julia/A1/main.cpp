#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
int main()
{
  Shape* shapes[] = { new Circle(25.5, point_t{ 1.05, 23.7 }),
    new Rectangle(rectangle_t{30.0, 10.67, point_t{12.3, 10.0}}) };
  for (Shape* shape : shapes)
  {
    std::cout << "The shape: ";
    shape->print(std::cout);
    const rectangle_t frameRectangle = shape->getFrameRect(); 
    std::cout << "\nIt's frame rectangle:  width = " << frameRectangle.width << "; height = "
      << frameRectangle.height << "; pos(" << frameRectangle.pos.x << ", " << frameRectangle.pos.y << ")\n";
    std::cout << "It's area: " << shape->getArea() << std::endl;
    const double dx = 10.0;
    const double dy = -34.3;
    shape->move(dx, dy);
    std::cout << "The shape, moved along the vector {" << dx << ", " << dy << "}: ";
    shape->print(std::cout);
    std::cout << std::endl;
    const point_t destination = {-4.0, 17.5};
    shape->move(destination);
    std::cout << "The shape, moved to the point (" << destination.x << ", " << destination.y << "): ";
    shape->print(std::cout);
    std::cout << std::endl << std::endl;
    delete shape;
  }
  return 0;
}
