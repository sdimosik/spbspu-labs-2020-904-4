#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  try
  {
    std::cout << "Rectangle test:\n";
    kichigin::point_t firstRectPosition{ 1.0, 2.0 };
    kichigin::Rectangle rect(3.2, 2.3, firstRectPosition);
    std::cout << "Width of rectangle is: " << rect.getWidth() << '\n'
        << "Height of rectangle is: " << rect.getHeight() << '\n'
        << "Coordinates of rectangle before moving are: (" << rect.getPosition().x
        << "," << rect.getPosition().y << ")\nArea of rectangle is: " << rect.getArea() << '\n';
    rect.scale(0.5);
    std::cout << "After scale with coefficient 0.5 width of rectangle is: " << rect.getWidth() << '\n'
        << "Height of rectangle is: " << rect.getHeight() << '\n'
        << "Coordinates of rectangle before moving are: (" << rect.getPosition().x
        << "," << rect.getPosition().y << ")\nArea of rectangle is: " << rect.getArea() << '\n';
    kichigin::point_t secondRectPosition{ 5.0, 6.0 };
    rect.move(secondRectPosition);
    std::cout << "Coordinates of rectangle after moving to (5,6) are: ("
        << rect.getPosition().x << "," << rect.getPosition().y << ")\n";
    std::cout << "Circle test:\n";
    kichigin::point_t firstCirclePosition{ -1.0, 3.0 };
    kichigin::Circle cirle(3.5, firstCirclePosition);
    std::cout << "Radius of circle is: " << cirle.getRadius() << '\n'
        << "Coordinates of circle are: (" << cirle.getPosition().x
        << "," << cirle.getPosition().y << ")" << '\n'
        << "Area of circle is: " << cirle.getArea() << '\n';
    cirle.scale(2.0);
    std::cout << "After scale with coefficient 2.0 radius of circle is: " << cirle.getRadius() << '\n'
        << "Coordinates of circle are: (" << cirle.getPosition().x
        << "," << cirle.getPosition().y << ")" << '\n'
        << "Area of circle is: " << cirle.getArea() << '\n';
    kichigin::point_t secondCirclePosition{ -3.0, 1.0 };
    cirle.move(secondCirclePosition);
    std::cout << "Coordinates of rectangle after moving to (-3,1) are: ("
        << cirle.getPosition().x << "," << cirle.getPosition().y << ")\nTest of polymorphism:\n";
    kichigin::Shape* shape = &rect;
    std::cout << "Now pointer to shape refers to rectangle and its area is: "
        << shape->getArea() << '\n';
    shape = &cirle;
    std::cout << "Now pointer to shape refers to circle and its area is: "
        << shape->getArea() << '\n';
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what() << "\nEnd of programm\n";
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown problem\nEnd of programm\n";
    return 2;
  }
  return 0;
}
