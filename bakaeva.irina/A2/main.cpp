#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  try
  {
    bakaeva::Rectangle rectangle(2.5, 4.0, {5.0, 5.0});
    bakaeva::Shape *shape = &rectangle;
    std::cout << " Before change:\n";
    shape->printData();
    std::cout << "Rectangle area: " << shape->getArea() << '\n';

    shape->move(-3.0, 2.5);
    std::cout << " After shifting in coordinates:\n";
    shape->printData();
    std::cout << "Rectangle area: " << shape->getArea() << '\n';

    bakaeva::point_t point{3.25, -1.1};
    shape->move(point);
    std::cout << " After moving to the point:\n";
    shape->printData();
    std::cout << "Rectangle area: " << shape->getArea() << '\n';

    std::cout << " After scaling with coefficient 1.5:\n";
    shape->scale(1.5);
    shape->printData();
    std::cout << "Rectangle area: " << shape->getArea() << '\n';

    bakaeva::Circle circle(4.0, {1.0, 4.7});
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

    std::cout << " After scaling with coefficient 3.1:\n";
    shape->scale(3.1);
    shape->printData();
    std::cout << "Circle area: " << shape->getArea() << '\n';
  }
  catch (const std::exception &exc)
  {
    std::cerr << exc.what() << std::endl;
    return -1;
  }
  catch (...)
  {
    std::cerr << "Program error!" << std::endl;
    return -1;
  }
  return 0;
}
