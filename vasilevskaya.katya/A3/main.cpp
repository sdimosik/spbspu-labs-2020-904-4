#include <iostream>
#include <stdexcept>
#include "base-types.hpp"
#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"

void moveShape(vasilevskaya::Shape::PointToShape& shape);

using Rectangle = vasilevskaya::Rectangle;
using Circle = vasilevskaya::Circle;
using Triangle = vasilevskaya::Triangle;

int main()
{
  try
  {
    vasilevskaya::Shape::PointToShape rectangle
      = std::make_shared<Rectangle>(2.6, 8, vasilevskaya::point_t{ 4, 8.4 });
    std::cout << rectangle->getArea() << "\n";
    rectangle->scale(3.8);
    rectangle->printFigure();
    rectangle->scale(0.3);
    rectangle->printFigure();
    rectangle->getFrameRect();
    std::cout << '\n';

    vasilevskaya::Shape::PointToShape triangle
      = std::make_shared<Triangle>(vasilevskaya::point_t{ 2, 1 }, vasilevskaya::point_t{ 6, 1 }, vasilevskaya::point_t{ 2, 8 });
    std::cout << triangle->getArea() << "\n";
    triangle->scale(2.5);
    triangle->printFigure();
    triangle->scale(4.1);
    triangle->getFrameRect();
    std::cout << '\n';

    vasilevskaya::Shape::PointToShape circle
      = std::make_shared<Circle>(vasilevskaya::point_t{ -7, -4 }, 2);
    std::cout << circle->getArea() << "\n";
    circle->scale(0.5);
    circle->printFigure();
    circle->scale(5);
    circle->printFigure();
    circle->getFrameRect();
    std::cout << "\n";

    std::cout << "\n\nCompositeShape\n";
    vasilevskaya::CompositeShape setShape(3);
    setShape.pushBack(rectangle);
    std::cout << setShape.getCount() << '\n';
    setShape.getFrameRect();
    setShape.printFigure();
    setShape.pushBack(circle);
    setShape.printFigure();
    vasilevskaya::Shape::PointToShape temporaryRectangle
      = std::make_shared<Rectangle>(5, 6, vasilevskaya::point_t{ 1, 6 });
    vasilevskaya::Shape::PointToShape temporaryTriangle
      = std::make_shared<Triangle>(vasilevskaya::point_t{ 5, 2 }, vasilevskaya::point_t{ 2, 4 }, vasilevskaya::point_t{ 3, 8 });
    vasilevskaya::Shape::PointToShape temporaryCircle
      = std::make_shared<Circle>(vasilevskaya::point_t{ 1, 1 }, 4);
    setShape.pushBack(temporaryCircle);
    setShape.pushBack(temporaryRectangle);
    setShape.pushBack(temporaryTriangle);
    setShape.printFigure();
    std::cout << setShape.getCount() << '\n' << setShape.getCapacity() << '\n'
      << setShape.getArea() << '\n';
    setShape.remove(2);
    setShape.printFigure();
    setShape.remove(2);
    std::cout << setShape.getCount() << '\n' << setShape.getCapacity() << '\n'
      << setShape.getArea() << '\n';
    setShape.printFigure();
    setShape.move(-4, 9.65);
    setShape.printFigure();
    vasilevskaya::point_t newCenterFrameRectangle{ 1, 1 };
    setShape.move(newCenterFrameRectangle);
    setShape.printFigure();
    setShape.scale(2);
    setShape.printFigure();
    setShape.scale(0.5);
    setShape.printFigure();

    return 0;
  }
  catch (const std::exception & err)
  {
    std::cerr << err.what() << std::endl;
    return -1;
  }
  catch (...)
  {
    std::cerr << "Error: Unknown error" << std::endl;
    return -2;
  }
}

void moveShape(vasilevskaya::Shape::PointToShape& shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Shape - an empty pointer, please give it an address!\n");
  }
  shape->printFigure();
  std::cout << "\n";
  vasilevskaya::point_t newPoint{ -1, 1 };
  shape->move(newPoint);
  shape->printFigure();
  std::cout << "\n";
  shape->move(-5.2, 6.4);
  shape->printFigure();
  std::cout << "\n";
}
