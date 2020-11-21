#include <iostream>
#include <stdexcept>
#include "base-types.hpp"
#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

void moveShape(vasilevskaya::Shape* shape);

void moveShape(vasilevskaya::Shape* shape)
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

int main()
{
  try
  {
    vasilevskaya::Rectangle myRectangle{ 2.6, 8, {4, 8.4} };
    vasilevskaya::Shape* shape = &myRectangle;
    std::cout << shape->getArea() << "\n";
    moveShape(shape);
    shape->scale(3.8);
    shape->printFigure();
    shape->scale(0.3);
    shape->printFigure();
    shape->getFrameRect();
    std::cout << '\n';

    vasilevskaya::Triangle myTriangle({ 2, 1 }, { 6, 1 }, { 2, 8 });
    shape = &myTriangle;
    std::cout << shape->getArea() << "\n";
    moveShape(shape);
    shape->scale(2.5);
    shape->printFigure();
    shape->scale(4.1);
    shape->getFrameRect();
    std::cout << '\n';

    vasilevskaya::Circle myCircle{ {-7, 4}, 2 };
    shape = &myCircle;
    std::cout << shape->getArea() << "\n";
    shape->scale(0.5);
    shape->printFigure();
    shape->scale(5);
    shape->printFigure();
    shape->getFrameRect();
    std::cout << "\n";
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
