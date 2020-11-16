#include <iostream>
#include <stdexcept>

#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

int main()
{
  try
  {
    unzhakov::Shape *shape;
    unzhakov::Circle circle(5.5, {1.1, 2.2});
    shape = &circle;
    shape->printArea();
    shape->printData();
    shape->printFrameRectangle();
    shape->move(1.3, 4.5);
    shape->printData();
    shape->move({3.3, 3.3});
    shape->printData();
    shape->scale(2);
    shape->printData();
    std::cout << '\n';

    unzhakov::Rectangle rectangle(2.2, 3.3, {4.4, 5.5});
    shape = &rectangle;
    shape->printArea();
    shape->printData();
    shape->printFrameRectangle();
    shape->move(1.3, 4.5);
    shape->printData();
    shape->move({3.3, 3.3});
    shape->printData();
    shape->scale(2);
    shape->printData();
    std::cout << '\n';

    unzhakov::Triangle triangle({1.1, 3.3}, {2.2, -5.5}, {-8.8, 4.4});
    shape = &triangle;
    shape->printArea();
    shape->printData();
    shape->printFrameRectangle();
    shape->move(1.3, 4.5);
    shape->printData();
    shape->move({3.3, 3.3});
    shape->printData();
    shape->scale(2);
    shape->printData();
  }
  catch (const std::exception &exc)
  {
    std::cerr << exc.what() << '\n';
    return -1;
  }
  return 0;
}
