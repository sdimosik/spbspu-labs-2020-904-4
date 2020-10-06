#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "matrix.hpp"
#include "composite-shape.hpp"
#include "polygon.hpp"
#include "triangle.hpp"

int main()
{
  rodion::Rectangle rectangle({2, 4, {5, 5}});
  rodion::Circle circle(2, {0, 0});
  rodion::Triangle triangle({8, 13}, {9, 3}, {10, -1});
  rectangle.rotate(180);
  rodion::CompositeShape compositeShape(4);
  std::shared_ptr<rodion::Shape> shape1 = std::make_shared<rodion::Rectangle>(rectangle);
  compositeShape.addShape(shape1);
  std::shared_ptr<rodion::Shape> shape2 = std::make_shared<rodion::Circle>(circle);
  compositeShape.addShape(shape2);
  std::shared_ptr<rodion::Shape> shape3 = std::make_shared<rodion::Triangle>(triangle);
  compositeShape.addShape(shape3);
  std::shared_ptr<rodion::Shape> shape4 =
      std::make_shared<rodion::Polygon>(rodion::Polygon({{11, 3}, {13, 3}, {13, 7}, {11, 7}}));
  compositeShape.addShape(shape4);
  std::cout << compositeShape.getArea() << "\n";
  compositeShape.scale(2);
  std::cout << compositeShape.getArea() << "\n";
  rodion::Matrix matrix;
  matrix.addShape(shape1);
  matrix.addShape(shape2);
  rodion::Matrix matrix2 = compositeShape.toMatrix();
  compositeShape.rotate(-1000);
  return 0;
}
