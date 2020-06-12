#include <iostream>
#include "circle.hpp"
#include "triangle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

int main()
{
  std::shared_ptr<anastasiev::Shape> rectangle
      = std::make_shared<anastasiev::Rectangle>(anastasiev::Rectangle(5.0, 3.0, {0.0, 5.0})),
      circle = std::make_shared<anastasiev::Circle>(anastasiev::Circle(5.0, {0.0, 60.0})),
      triangle = std::make_shared<anastasiev::Triangle>(anastasiev::Triangle({0.0, 0.0}, {3.0, 0.0}, {0.0, 4.0}));
  anastasiev::CompositeShape compositeShape;
  compositeShape.add(rectangle);
  compositeShape.add(circle);
  compositeShape.add(triangle);
  std::cout <<"Composite shape size -" << compositeShape.getSize() << '\n'
      << "Composite shape area - " << compositeShape.getArea() << '\n';
  compositeShape.move(1.0, 5.0);
  std::cout << "Composite shape area after moving - " << compositeShape.getArea() << '\n';
  anastasiev::rectangle_t frame = compositeShape.getFrameRect();
  std::cout << "Area of frame -" << frame.width * frame.height << '\n';
  compositeShape.scale(2.0);
  std::cout << "Composite shape area after scale(2.0) - " << compositeShape.getArea() << '\n';
  frame = compositeShape.getFrameRect();
  std::cout << "Area of frame after scale (2.0)-" << frame.width * frame.height << '\n';
  compositeShape.remove(0);
  std::cout << "Composite shape area after after removing rectangle - " << compositeShape.getArea() << '\n';
  return 0;
}
