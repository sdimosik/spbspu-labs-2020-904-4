#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

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
  compShape.rotate(90.0);
  compShape.printCompositeShapeData();
  compShape.removeShape(1);
  compShape.printCompositeShapeData();

  std::cout << "\nMATRIX:\n";
  spasoevich::Matrix matrix;
  spasoevich::Rectangle rect4({ 0.0, 5.0 }, 3.6, 6.7);
  spasoevich::Circle circ4({ 5.0, 10.0 }, 3.9);
  spasoevich::Rectangle rect5({ 2.0, 4.0 }, 9.6, 6.7);
  spasoevich::Circle circ5({ 9.0, 10.0 }, 3.3);
  spasoevich::Matrix::shape_ptr shape5 = std::make_shared<spasoevich::Rectangle>(rect4);
  spasoevich::Matrix::shape_ptr shape6 = std::make_shared<spasoevich::Circle>(circ4);
  spasoevich::Matrix::shape_ptr shape7 = std::make_shared<spasoevich::Rectangle>(rect5);
  spasoevich::Matrix::shape_ptr shape8 = std::make_shared<spasoevich::Circle>(circ5);
  matrix.addShape(shape5);
  matrix.addShape(shape6);
  matrix.addShape(shape7);
  matrix.addShape(shape8);
  matrix.printMatrixData();

  return 0;
}
