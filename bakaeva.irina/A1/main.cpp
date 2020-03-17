#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  try
  {
    Rectangle rectangle(2.5, 4.0, {5.0, 5.0});
    Shape *shape = &rectangle;
    std::cout << " Before change:\n";
    shape->printData();
    std::cout << "Rectangle area: " << shape->getArea() << '\n';

    shape->move(-3.0, 2.5);
    std::cout << " After shifting in coordinates:\n";
    shape->printData();
    std::cout << "Rectangle area: " << shape->getArea() << '\n';

    point_t point{3.25, -1.1};
    shape->move(point);
    std::cout << " After moving to the point:\n";
    shape->printData();
    std::cout << "Rectangle area: " << shape->getArea() << '\n';

    Circle circle(4.0, {1.0, 4.7});
    shape = &circle;
    std::cout << " Before change:\n";
    shape->printData();
    std::cout << "Circle area: " << shape->getArea() << '\n';
    shape->printFrameRect();

    shape->move(-2.0, 3.55);
    std::cout << " After shifting in coordinates:\n";
    shape->printData();
    std::cout << "Circle area: " << shape->getArea() << '\n';
    shape->printFrameRect();

    shape->move(point);
    std::cout << " After moving to the point:\n";
    shape->printData();
    std::cout << "Circle area: " << shape->getArea() << '\n';
    shape->printFrameRect();
  }
  catch (const std::exception &exc)
  {
    std::cerr <<  exc.what() << '\n';
    return -1;
  }
  catch(...)
  {
    std::cerr << "Program error!\n";
    return -1;
  }
  return 0;
}
