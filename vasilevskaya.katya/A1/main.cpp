#include <iostream>
#include <stdexcept>
#include "base-types.hpp"
#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

void moveShape(Shape* shape);

void moveShape(Shape* shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Shape - an empty pointer, please give it an address!\n");
  }
  shape->printFigure();
  std::cout << "\n";
  point_t newPoint{ -1, 1 };
  shape->move(newPoint);
  shape->printFigure();
  std::cout << "\n";
  shape->move(-5.2, 6.4);
  shape->printFigure();
  std::cout << "\n";
}

int main()
{
  try
  {
    Rectangle myRectangle{ 2.6, 8, {4, 8.4} };
    Shape* shape = &myRectangle;
    std::cout << shape->getArea() << "\n";
    moveShape(shape);
    shape->printFigure();
    std::cout << '\n';

    Triangle myTriangle(point_t{ 2, 1 }, point_t{ 6, 1 }, point_t{ 2, 8 });
    shape = &myTriangle;
    std::cout << shape->getArea() << "\n";
    moveShape(shape);
    shape->printFigure();
    std::cout << '\n';

    Circle myCircle{ {-7, 4}, 2 };
    shape = &myCircle;
    std::cout << shape->getArea() << "\n";
    moveShape(shape);
    shape->printFigure();
    std::cout << "\n";
  return 0;
  }
  catch (std::invalid_argument & variable)
  {  
    std::cerr << "A serious error has happened! Further execution of the program is not possible\n";
    return 1;
  }
}
