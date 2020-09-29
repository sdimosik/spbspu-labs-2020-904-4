#include <iostream>
#include "triangle.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

int main()
{
  try
  {
    std::cout << "Composite shape test" << '\n';
    rodion::Rectangle rectangle({2, 4, {-1, 0}});
    rodion::Circle circle(5, {1, 0});
    rodion::Triangle triangle({1, 5}, {-5, 3}, {5, 2});
    rodion::CompositeShape compositeShape(3);
    std::shared_ptr<rodion::Shape> shape1 = std::make_shared<rodion::Rectangle>(rectangle);
    compositeShape.addShape(shape1);
    std::shared_ptr<rodion::Shape> shape2 = std::make_shared<rodion::Circle>(circle);
    compositeShape.addShape(shape2);
    std::shared_ptr<rodion::Shape> shape3 = std::make_shared<rodion::Triangle>(triangle);
    compositeShape.addShape(shape3);
    compositeShape.show();
    std::cout << "Composite Shape area before scale: " << compositeShape.getArea() << '\n';
    compositeShape.scale(2);
    std::cout << "Composite Shape area after scale (scale factor = 2): "<< compositeShape.getArea() << '\n';
  }
  catch (const std::invalid_argument &exception)
  {
    std::cerr << exception.what() << '\n';
    return 1;
  }
  catch (const std::out_of_range &exception)
  {
    std::cerr << exception.what() << '\n';
    return 2;
  }
  catch (...)
  {
    std::cerr << "Unknown problem" << '\n';
    return 3;
  }
  return 0;
 try
 {
   std::cout << "Composite shape test" << '\n';
   rodion::Rectangle rectangle({2, 4, {-1, 0}});
   rodion::Circle circle(5, {1, 0});
   rodion::Triangle triangle({1, 5}, {-5, 3}, {5, 2});
   rodion::CompositeShape compositeShape(3);
   std::shared_ptr<rodion::Shape> shape1 = std::make_shared<rodion::Rectangle>(rectangle);
   compositeShape.addShape(shape1);
   std::shared_ptr<rodion::Shape> shape2 = std::make_shared<rodion::Circle>(circle);
   compositeShape.addShape(shape2);
   std::shared_ptr<rodion::Shape> shape3 = std::make_shared<rodion::Triangle>(triangle);
   compositeShape.addShape(shape3);
   compositeShape.show();
   std::cout << "Composite Shape area before scale: " << compositeShape.getArea() << '\n';
   compositeShape.scale(2);
   std::cout << "Composite Shape area after scale (scale factor = 2): "<< compositeShape.getArea() << '\n';
 }
 catch (const std::invalid_argument &exception)
 {
   std::cerr << exception.what() << '\n';
   return 1;
 }
 catch (const std::out_of_range &exception)
 {
   std::cerr << exception.what() << '\n';
   return 2;
 }
 catch (...)
 {
   std::cerr << "Unknown problem" << '\n';
   return 3;
 }
 return 0;
}

