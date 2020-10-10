
#include <iostream>
#include "../common/rectangle.hpp"
#include "../common/circle.hpp"
#include "../common/triangle.hpp"
#include "../common/composite-shape.hpp"
#include "../common/matrix.hpp"
#include "../common/polygon.hpp"

int main()
{
  pashnin::point_t dot1{10, 10}, dot2{9, 8}, dot3{2, 0};
  pashnin::Rectangle rectangle(2, 5, dot1);
  pashnin::Circle circle(3, dot2);
  pashnin::Triangle triangle(dot1, dot2, dot3);
  rectangle.rotate(-540);
  circle.rotate(-999);
  triangle.rotate(-450);
  pashnin::CompositeShape compositeShape(4);
  std::shared_ptr<pashnin::Shape> shape1 = std::make_shared<pashnin::Rectangle>(rectangle);
  compositeShape.addShape(shape1);
  std::shared_ptr<pashnin::Shape> shape2 = std::make_shared<pashnin::Circle>(circle);
  compositeShape.addShape(shape2);
  std::shared_ptr<pashnin::Shape> shape3 = std::make_shared<pashnin::Triangle>(triangle);
  compositeShape.addShape(shape3);
  std::shared_ptr<pashnin::Shape> shape4 =
    std::make_shared<pashnin::Polygon>(pashnin::Polygon({dot1, dot2, dot3, {5, 4}}));
  compositeShape.addShape(shape4);
  std::cout << compositeShape.getArea() << "\n";
  compositeShape.scale(3);
  compositeShape.rotate(1260);
  std::cout << compositeShape.getArea() << "\n";
  pashnin::Matrix matrix;
  matrix.addShape(shape1);
  matrix.addShape(shape2);
  matrix.addShape(shape3);
  matrix.addShape(shape4);
  pashnin::Matrix matrix1 = compositeShape.toMatrix();
  return 0;
}
