#include <iostream>

#include"circle.hpp"
#include"rectangle.hpp"
#include"triangle.hpp"

int main()
{
  Shape* shape;

  Circle circle(5.5, { 1.1, 2.2 });
  shape = &circle;
  shape->printArea();
  shape->printData();
  shape->printFrameRectangle();
  shape->move(1.3, 4.5);
  shape->printData();
  shape->move({ 3.3, 3.3 });
  shape->printData();
  std::cout << '\n';

  Rectangle rectangle(2.2, 3.3, { 4.4, 5.5 });
  shape = &rectangle;
  shape->printArea();
  shape->printData();
  shape->printFrameRectangle();
  shape->move(1.3, 4.5);
  shape->printData();
  shape->move({ 3.3, 3.3 });
  shape->printData();
  std::cout << '\n';

  Triangle triangle({ 1.1, 3.3 }, { 2.2, -5.5 }, { -8.8, 4.4 });
  shape = &triangle;
  shape->printArea();
  shape->printData();
  shape->printFrameRectangle();
  shape->move(1.3, 4.5);
  shape->printData();
  shape->move({ 3.3, 3.3 });
  shape->printData();
  std::cout << '\n';

 /* try
  {
    Circle circle(-5.5, { 1.1,2.2 });
  }
  catch (const std::invalid_argument& exc)
  {
    std::cerr << exc.what() << '\n';
  }

  try
  {
    Rectangle rectangle(-2.2, 3.3, { 4.4,5.5 });
  }
  catch (const std::invalid_argument& exc)
  {
    std::cerr << exc.what() << '\n';
  }

  try
  {
    Rectangle rectangle(2.2, -3.3, { 4.4,5.5 });
  }
  catch (const std::invalid_argument& exc)
  {
    std::cerr << exc.what() << '\n';
  }

  try
  {
    Triangle triangle({ 1.1, 3.3 }, { 2.2, 3.3 }, { -8.8, 3.3 });
  }
  catch (const std::invalid_argument& exc)
  {
    std::cerr << exc.what() << '\n';
  }

  try
  {
    Triangle triangle({ 1.1, 3.3 }, { 1.1, -5.5 }, { 1.1, 4.4 });
  }
  catch (const std::invalid_argument& exc)
  {
    std::cerr << exc.what() << '\n';
  }

  try
  {
    Triangle triangle({ 1.1, 3.3 }, { 1.1, 3.3 }, { 1.1, 3.3 });
  }
  catch (const std::invalid_argument& exc)
  {
    std::cerr << exc.what() << '\n';
  }*/

  return 0;
}
