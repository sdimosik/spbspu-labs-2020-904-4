#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

int main()
{
  try
  {
    point_t point{2.0, 4.0};
    Circle circle({0.0, 0.0}, 2.0);
    Shape *shape = &circle;

    std::cout << "Circle after creation: ";
    shape->print();
    std::cout << "Circle area: " << shape->getArea() << std::endl;
    std::cout << "Frame rectangle: ";
    shape->printFrameRectangle();

    shape->move(1.0, 2.0);
    std::cout << "After shifting by 1 in X axis and 2 in Y axis: ";
    shape->print();
    std::cout << "Circle area: " << shape->getArea() << std::endl;
    std::cout << "Frame rectangle: ";
    shape->printFrameRectangle();

    shape->move(point);
    std::cout << "After moving to the point (2, 4): ";
    shape->print();
    std::cout << "Circle area: " << shape->getArea() << std::endl;
    std::cout << "Frame rectangle: ";
    shape->printFrameRectangle();

    std::cout << std::endl;

    Rectangle rectangle(2.0, 4.0, {3.0, 3.0});
    shape = &rectangle;

    std::cout << "Rectangle after creation: ";
    shape->print();
    std::cout << "Rectangle area: " << shape->getArea() << std::endl;
    std::cout << "Frame rectangle: ";
    shape->printFrameRectangle();

    shape->move(1.0, 2.0);
    std::cout << "After shifting by 1 in X axis and 2 in Y axis: ";
    shape->print();
    std::cout << "Rectangle area: " << shape->getArea() << std::endl;
    std::cout << "Frame rectangle: ";
    shape->printFrameRectangle();

    shape->move(point);
    std::cout << "After moving to the point (2, 4): ";
    shape->print();
    std::cout << "Rectangle area: " << shape->getArea() << std::endl;
    std::cout << "Frame rectangle: ";
    shape->printFrameRectangle();

    std::cout << std::endl;

    Triangle triangle({0.0, 0.0}, {0.0, 4.0}, {4.0, 0.0});
    shape = &triangle;

    std::cout << "Triangle after creation: ";
    shape->print();
    std::cout << "Triangle area: " << shape->getArea() << std::endl;
    std::cout << "Frame rectangle: ";
    shape->printFrameRectangle();

    shape->move(1.0, 2.0);
    std::cout << "After shifting by 1 in X axis and 2 in Y axis: ";
    shape->print();
    std::cout << "Triangle area: " << shape->getArea() << std::endl;
    std::cout << "Frame rectangle: ";
    shape->printFrameRectangle();

    shape->move(point);
    std::cout << "After moving to the point (2, 4): ";
    shape->print();
    std::cout << "Triangle area: " << shape->getArea() << std::endl;
    std::cout << "Frame rectangle: ";
    shape->printFrameRectangle();
  }
  catch (const std::exception& err)
  {
    std::cerr << err.what() << std::endl;
    return -1;
  }
  catch (...)
  {
    std::cerr << "Error: Unknown error" << std::endl;
    return -2;
  }
  return 0;
}
