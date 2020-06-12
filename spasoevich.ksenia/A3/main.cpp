#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

int main()
{
  std::cout << "COMPOSITE SHAPES: \n";
  spasoevich::Rectangle rect3({ 2.7, 3.6 }, 5.7, 2.4);
  spasoevich::Circle circ3({ 1.6, 6.5 }, 5.6);
  spasoevich::CompositeShape::shape_ptr rectangle = std::make_shared<spasoevich::Rectangle>(rect3);
  spasoevich::CompositeShape::shape_ptr circle = std::make_shared<spasoevich::Circle>(circ3);
  spasoevich::CompositeShape compShape;
  std::cout << "Added rectangle: center(2.7, 3.6), height=2.4, width=5.7\n";
  std::cout << "Added circle: center(1.6, 6.5), radius=5.6\n";
  compShape.addShape(rectangle);
  compShape.addShape(circle);
  compShape.printCompositeShapeData();
  compShape.move(2.3, 5.6);
  compShape.printCompositeShapeData();
  compShape.move({ 2.3, 5.6 });
  compShape.printCompositeShapeData();
  compShape.scale(8);
  compShape.printCompositeShapeData();
  compShape.removeShape(1);
  compShape.printCompositeShapeData();
  return 0; 
}
