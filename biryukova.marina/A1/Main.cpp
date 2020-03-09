#include <cassert>
#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  Circle circle1(point_t{1.8,4.2}, 8.1);
  Circle circle2(point_t{3.8,7.0}, 1.4);
  Shape* shapes[] = {&circle1, &circle2};
  for (int i = 0; i < 2; i++)
  {
    std::cout << "Starting position of shape " << i+1 << ":\n";
    shapes[i]->print();
    std::cout << "Area of shape " << i + 1 << ": ";
    std::cout << shapes[i]->getArea() << '\n';
    Rectangle rec(shapes[i]->getFrameRect());
    std::cout << "The frame rectangle of shape " << i + 1 << ":\n";
    rec.print();
    shapes[i]->move(point_t{1,0});
    std::cout << "New position of shape " << i + 1 << ":\n";
    shapes[i]->print();
  }
  Rectangle rectangle1(point_t{3.0, 7.1}, 9.4, 2.4);
  Rectangle rectangle2(point_t{6.9, 5.2}, 9.0, 10.5);
  shapes[0] = &rectangle1;
  shapes[1] = &rectangle2;
  for (int i = 0; i < 2; i++)
  {
    std::cout << "Starting position of shape " << i + 1 << ":\n";
    shapes[i]->print();
    std::cout << "Area of shape " << i + 1 << ": ";
    std::cout << shapes[i]->getArea() << '\n';
    Rectangle rec(shapes[i]->getFrameRect());
    std::cout << "The frame rectangle of shape " << i + 1 << ":\n";
    rec.print();
    shapes[i]->move(0.7, 3.6);
    std::cout << "New position of shape " << i + 1 << ":\n";
    shapes[i]->print();
  }
  return 0;
}
