#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include <iostream>

int main() {
  try {
    Shape *shapeRect = new Rectangle(3, 5, point_t{4, 4});
    std::cout << "Rectangle area - " << shapeRect->getArea() << '\n';
    delete shapeRect;
    Shape *shapeCirc = new Circle(5, point_t{0, 1});
    std::cout << "Circle area - " << shapeCirc->getArea() << '\n';
    delete shapeCirc;
    Shape *shapeTri = new Triangle(point_t{0, 0}, point_t{0, 3}, point_t{4, 0});
    std::cout << "Triangle area - " << shapeTri->getArea() << '\n';
    delete shapeTri;
    Triangle triangle(point_t{2, 1}, point_t{6, 1}, point_t{2, 8});
    std::cout << "\nNew trinagle created.\nTriangle area - " << triangle.getArea() << '\n'
              << "Triangle position - (" << triangle.getPosition().x <<"; "<< triangle.getPosition().y << ")\n";
    rectangle_t frame = triangle.getFrameRect();
    point_t posOfFrame = frame.pos;
    std::cout << "Width of frame of triangle - " << frame.width << '\n'
      << "Height of frame of triangle - " << frame.height << '\n'
      << "Position of frame of triangle - (" << posOfFrame.x << "; " << posOfFrame.y << ")\n"
      << "\nMoving triangle to point (0; 0)\n";
    triangle.move(point_t{0,0});
    std::cout << "Area of triangle after moving - " << triangle.getArea() <<'\n'
      << "Triangle position - (" << triangle.getPosition().x <<"; "<< triangle.getPosition().y << ")\n";
    frame = triangle.getFrameRect();
    posOfFrame = frame.pos;
    std::cout << "Width of frame of triangle - " << frame.width << '\n'
      << "Height of frame of triangle - " << frame.height << '\n'
      << "Position of frame of triangle - (" << posOfFrame.x << "; " << posOfFrame.y << ")\n";    
    return 0;
  }
  catch (const std::invalid_argument&)
  {
    std::cerr << "Invalid data.\n";
    return 1;
  }
  catch(...)
  {
    std::cerr << "Unknown error.\n";
    return 2;
  }
}
