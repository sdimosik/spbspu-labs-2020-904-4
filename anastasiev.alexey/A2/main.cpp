#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

int main()
{
  try
    {
    anastasiev::Shape *shapeRect = new anastasiev::Rectangle(3.0, 5.0, anastasiev::point_t{4.0, 4.0});
    std::cout << "Rectangle area - " << shapeRect->getArea() << '\n';
    delete shapeRect;
    anastasiev::Shape *shapeCirc = new anastasiev::Circle(5.0, anastasiev::point_t{0.0, 1.0});
    std::cout << "Circle area - " << shapeCirc->getArea() << '\n';
    delete shapeCirc;
    anastasiev::Shape *shapeTri = new anastasiev::Triangle(anastasiev::point_t{0.0, 0.0},
        anastasiev::point_t{0.0, 3.0}, anastasiev::point_t{4.0, 0.0});
    std::cout << "Triangle area - " << shapeTri->getArea() << '\n';
    delete shapeTri;
    anastasiev::Triangle triangle(anastasiev::point_t{2.0, 1.0},
        anastasiev::point_t{6, 1}, anastasiev::point_t{2.0, 8.0});
    std::cout << "\nNew trinagle created.\nTriangle area - " << triangle.getArea() << '\n'
        << "Triangle position - (" << triangle.getPosition().x <<"; "<< triangle.getPosition().y << ")\n";
    anastasiev::rectangle_t frame = triangle.getFrameRect();
    anastasiev::point_t posOfFrame = frame.pos;
    std::cout << "Width of frame of triangle - " << frame.width << '\n'
        << "Height of frame of triangle - " << frame.height << '\n'
        << "Position of frame of triangle - (" << posOfFrame.x << "; " << posOfFrame.y << ")\n"
        << "\nMoving triangle to point (0.0; 0.0)\n";
    triangle.move(anastasiev::point_t{0.0, 0.0});
    std::cout << "Area of triangle after moving - " << triangle.getArea() <<'\n'
        << "Triangle position - (" << triangle.getPosition().x <<"; "<< triangle.getPosition().y << ")\n";
    frame = triangle.getFrameRect();
    posOfFrame = frame.pos;
    std::cout << "Width of frame of triangle - " << frame.width << '\n'
        << "Height of frame of triangle - " << frame.height << '\n'
        << "Position of frame of triangle - (" << posOfFrame.x << "; " << posOfFrame.y << ")\n";
    std::cout << "Area of triangle - " << triangle.getArea() <<'\n';
    triangle.scale(2.0);
    std::cout << "Area of triangle after scale(2.0) - "<< triangle.getArea() << "\n\n";
    anastasiev::Circle circle(5.0, {0.0, 0.0});
    std::cout << "Area of circle - " << circle.getArea() << '\n';
    circle.scale(0.5);
    std::cout << "Area of circle after scale(0.5) - " << circle.getArea() << "\n\n";
    anastasiev::Rectangle rectangle(2.0, 5.0, {0.0, 0.0});
    std::cout << "Area of rectangle - " << rectangle.getArea() << '\n';
    rectangle.scale(5.0);
    std::cout << "Area of rectangle after scale(5.0) - " << rectangle.getArea() << '\n';
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
