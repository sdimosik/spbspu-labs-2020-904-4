#include <iostream>
#include "../common/circle.hpp"
#include "../common/rectangle.hpp"
#include "../common/matrix.hpp"
#include "../common/composite-shape.hpp"
#include "../common/polygon.hpp"
#include "../common/triangle.hpp"

int main()
{
  vorotnikov::Rectangle rectangle(2, 4, {5, 5});
  vorotnikov::Circle circle(2, {0, 0});
  vorotnikov::Triangle triangle({8, 0}, {9, 3}, {10, 0} );
  rectangle.rotate(180);
  vorotnikov::CompositeShape compositeShape(4);
  std::shared_ptr<vorotnikov::Shape> shape1 = std::make_shared<vorotnikov::Rectangle>(rectangle);
  compositeShape.addShape(shape1);
  std::shared_ptr<vorotnikov::Shape> shape2 = std::make_shared<vorotnikov::Circle>(circle);
  compositeShape.addShape(shape2);
  std::shared_ptr<vorotnikov::Shape> shape3 = std::make_shared<vorotnikov::Triangle>(triangle);
  compositeShape.addShape(shape3);
  std::shared_ptr<vorotnikov::Shape> shape4 =
      std::make_shared<vorotnikov::Polygon>(vorotnikov::Polygon({{11, 3}, {13, 3}, {13, 7}, {11, 7}}));
  compositeShape.addShape(shape4);
  std::cout << compositeShape.getArea() << "\n";
  compositeShape.scale(2);
  std::cout << compositeShape.getArea() << "\n";
  vorotnikov::Matrix matrix;
  matrix.addShape(shape1);
  matrix.addShape(shape2);
  vorotnikov::Matrix matrix2 = compositeShape.toMatrix();
  compositeShape.rotate(-1000);
  return 0;
}
