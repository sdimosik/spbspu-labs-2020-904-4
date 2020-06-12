#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

int main()
{
  std::shared_ptr<kundik::Shape> rectangle = std::make_shared<kundik::Rectangle>(kundik::Rectangle({ 0., 0. }, 2., 2.));
  std::shared_ptr<kundik::Shape> circle = std::make_shared<kundik::Circle>(kundik::Circle({ 0., 3. }, 1.));
  kundik::CompositeShape compositeShape(2);
  compositeShape.addShape(rectangle);
  compositeShape.addShape(circle);
  std::cout << compositeShape.getArea() << "\n";
  compositeShape.scale(10);
  compositeShape.move(2, 2);
  std::cout << compositeShape.getArea() << "\n";
  std::cout << compositeShape.getSize() << "\n";
  std::cout << "Coordinates center: (" << compositeShape.getFrameRect().pos.x << ", " << compositeShape.getFrameRect().pos.y << ")" << std::endl;
  return 0;
}
