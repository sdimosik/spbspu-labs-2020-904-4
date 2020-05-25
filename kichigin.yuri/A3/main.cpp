#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

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
    kichigin::Circle circle(3.5, firstCirclePosition);
    std::cout << "Radius of circle is: " << circle.getRadius() << '\n'
        << "Coordinates of circle are: (" << circle.getPosition().x
        << "," << circle.getPosition().y << ")" << '\n'
        << "Area of circle is: " << circle.getArea() << '\n';
    circle.scale(2.0);
    std::cout << "After scale with coefficient 2.0 radius of circle is: " << circle.getRadius() << '\n'
        << "Coordinates of circle are: (" << circle.getPosition().x
        << "," << circle.getPosition().y << ")" << '\n'
        << "Area of circle is: " << circle.getArea() << '\n';
    kichigin::point_t secondCirclePosition{ -3.0, 1.0 };
    circle.move(secondCirclePosition);
    std::cout << "Coordinates of rectangle after moving to (-3,1) are: ("
        << circle.getPosition().x << "," << circle.getPosition().y << ")\nTest of polymorphism:\n";
    kichigin::Shape* shape = &rect;
    std::cout << "Now pointer to shape refers to rectangle and its area is: "
        << shape->getArea() << '\n';
    shape = &circle;
    std::cout << "Now pointer to shape refers to circle and its area is: "
        << shape->getArea() << "\nComposite shape test:\n";
    kichigin::CompositeShape compShape(1);
    std::cout << "Full size of composite shape is " << compShape.getFullSize() <<
        "\nCurrent size of composite shape is " << compShape.getCurrentSize();
    std::shared_ptr<kichigin::Shape> sharedPointer = std::make_shared<kichigin::Rectangle>(rect);
    compShape.addShape(sharedPointer);
    std::cout << "\nAfter adding first shape full size of composite shape is " << compShape.getFullSize() <<
        "\nCurrent size of composite shape is " << compShape.getCurrentSize();
    sharedPointer = std::make_shared<kichigin::Circle>(circle);
    compShape.addShape(sharedPointer);
    std::cout << "\nAfter adding second shape full size of composite shape is " << compShape.getFullSize()
        << "\nCurrent size of composite shape is " << compShape.getCurrentSize()
        << "\nArea of first shape in composite shape is " << compShape[0]->getArea()
        << "\nArea of second shape in composite shape is " << compShape[1]->getArea()
        << "\nTotal area of composite shape is "<< compShape.getArea()
        << "\nCoordinates of composite shape are (" << compShape.getFrameRect().pos.x << ','
        << compShape.getFrameRect().pos.y << ")\n";
    kichigin::point_t newCompShapePosition = { 5.0, 5.0 };
    compShape.move(newCompShapePosition);
    std::cout << "Coordinates of composite shape afmer moving to (5,5) are("
        << compShape.getFrameRect().pos.x << ',' << compShape.getFrameRect().pos.y << ")\n";
    compShape.scale(1.5);
    std::cout << "After scale with coefficient 1.5 area of composite shape is: "
        << compShape.getArea();
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what() << "\nEnd of programm\n";
    return 1;
  }
  catch (const std::out_of_range& error)
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
