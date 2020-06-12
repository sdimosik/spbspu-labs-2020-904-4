#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
int main()
{
  point_t point = { 80, 20 };
  double dx = 15;
  double dy = -15;
  Rectangle rectangle({ 3, 3 }, 6, 7);
  Circle circle({ 4, 5 }, 3);
  Triangle triangle({ 2, 4 }, { 4, 5 }, { 2, 7 });

  std::cout << rectangle << " area: " << rectangle.getArea() << '\n'
    << circle << " area: " << circle.getArea() << '\n'
    << triangle << " area: " << triangle.getArea() << '\n';

  rectangle.move(dx, dy);
  circle.move(dx, dy);
  triangle.move(dx, dy);

  std::cout << "After move(double, double)" << '\n'
     << rectangle << " area: " << rectangle.getArea() << '\n'
     << circle << " area: " << circle.getArea() << '\n'
     << triangle << " area: " << triangle.getArea() << '\n';

  rectangle.move(point);
  circle.move(point);
  triangle.move({ 1.5, 1.5 });

  std::cout << "After move(point_t)" << '\n'
    << rectangle << " area: " << rectangle.getArea() << '\n'
    << circle << " area: " << circle.getArea() << '\n'
    << triangle << " area: " << triangle.getArea() << '\n';

  rectangle_t rectangle_rectangle = rectangle.getFrameRect();
  rectangle_t rectangle_circle = circle.getFrameRect();
  rectangle_t rectangle_triangle = triangle.getFrameRect();

  std::cout << "Bound rectangles:" << '\n'
    << "Rectangle" << "(" << rectangle_rectangle.pos.x << "," << rectangle_rectangle.pos.y << ")" << "height = "
    << rectangle_rectangle.height << "width = " << rectangle_rectangle.width << '\n'
    << "Circle" << "(" << rectangle_circle.pos.x << "," << rectangle_circle.pos.y << ")" << "height = "
    << rectangle_rectangle.height << "width = " << rectangle_rectangle.width << '\n'
    << "Triangle" << "(" << rectangle_triangle.pos.x << "," << rectangle_triangle.pos.y << ")" << "height = "
    << rectangle_rectangle.height << "width = " << rectangle_rectangle.width << '\n';
  return 0;
}
