#include <iostream>
#include <memory>
#include <stdexcept>

#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"

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
    shape->rotate(50);
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
    shape->rotate(50);
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

    std::unique_ptr<unzhakov::CompositeShape> array = nullptr;
    std::shared_ptr<unzhakov::Rectangle> temp = std::make_shared<unzhakov::Rectangle>
      (2.345, 7.123, unzhakov::point_t{10, -15});
    array = std::make_unique<unzhakov::CompositeShape>();
    array->add(temp);
    array->add(std::make_shared<unzhakov::Rectangle>(21, 4, unzhakov::point_t{22, -8}));
    array->add(std::make_shared<unzhakov::Circle>(14, unzhakov::point_t{-2, 8}));
    array->add(std::make_shared<unzhakov::Triangle>
                 (unzhakov::point_t{-2, 8}, unzhakov::point_t{2, -8}, unzhakov::point_t{20, 18}));
    array->move(45, 345);
    array->printData();
    array->scale(12);
    array->printData();
    array->rotate(50);
    array->printData();
    array->remove(0);
    array->printData();
  }
  catch (const std::exception &exc)
  {
    std::cerr << exc.what() << '\n';
    return -1;
  }
  return 0;
}
