#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  lovkacheva::Shape *shapes[] = {new lovkacheva::Circle(25.5, lovkacheva::point_t{1.05, 23.7}),
                                 new lovkacheva::Rectangle(lovkacheva::rectangle_t{30.0, 10.67,
                                                                                   lovkacheva::point_t{12.3, 10.0}})};
  for (lovkacheva::Shape *shape : shapes)
  {
    std::cout << "The shape: ";
    shape->print(std::cout);
    const lovkacheva::rectangle_t frameRectangle = shape->getFrameRect();
    std::cout << "\nIts frame rectangle:  width = " << frameRectangle.width << "; height = "
              << frameRectangle.height << "; pos(" << frameRectangle.pos.x << ", " << frameRectangle.pos.y << ")\n";
    std::cout << "Its area: " << shape->getArea() << '\n';
    const double dx = 10.0;
    const double dy = -34.3;
    shape->move(dx, dy);
    std::cout << "The shape, moved along the vector {" << dx << ", " << dy << "}: ";
    shape->print(std::cout);
    std::cout << '\n';
    const lovkacheva::point_t destination = {-4.0, 17.5};
    shape->move(destination);
    std::cout << "The shape, moved to the point (" << destination.x << ", " << destination.y << "): ";
    shape->print(std::cout);
    std::cout << "\nThe shape, scaled using the coefficient 2.5: ";
    shape->scale(2.5);
    shape->print(std::cout);
    std::cout << "\nIts area: " << shape->getArea();
    std::cout << "\n\n";
    delete shape;
  }
  return 0;
}
