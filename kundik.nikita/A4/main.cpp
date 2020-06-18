#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

int main()
{
  std::shared_ptr<kundik::Shape> circle = std::make_shared<kundik::Circle>(kundik::Circle({ 1.0, 2.0 }, 2.0));
  std::shared_ptr<kundik::Shape> rectangle = std::make_shared<kundik::Rectangle>(kundik::Rectangle({ 8.0, 7.0 }, 4.0, 2.0));
  kundik::CompositeShape compositeShape(2);
  compositeShape.addShape(circle);
  compositeShape.addShape(rectangle);
  std::cout << compositeShape.getArea() << "\n";
  std::cout << "Center is : (" << compositeShape.getCentrer().x << ";" << compositeShape.getCentrer().y << ")\n";
  compositeShape.scale(10);
  compositeShape.move(2, 2);
  std::cout << compositeShape.getArea() << "\n";
  std::cout << compositeShape.getSize() << "\n";
  std::cout << "Center is : (" << compositeShape.getCentrer().x << ";" << compositeShape.getCentrer().y << ")\n";
  kundik::Matrix matrix;
  matrix.addShape(circle);
  matrix.addShape(rectangle);
  return 0;
}
