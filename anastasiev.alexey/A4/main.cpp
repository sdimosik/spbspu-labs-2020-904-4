#include <iostream>

#include "polygon.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
int main()
{
  try
  {
    std::shared_ptr<anastasiev::Shape> polygon
        = std::make_shared<anastasiev::Polygon>(anastasiev::Polygon({{2, 2}, {2, 5}, {5, 5}, {5, 2}}));
    std::cout << "Polygon area - " << polygon->getArea() << '\n';
    anastasiev::rectangle_t frame = polygon->getFrameRect();
    std::cout << "Width of polygon frame rect - " << frame.width
        <<"\nHeight of polygon frame rect - " << frame.height;
    polygon->rotate(45);
    frame = polygon->getFrameRect();
    std::cout << "\nPolygon area after rotate(45) - " << polygon->getArea()
        << "\nWidth of polygon frame rect after rotate(45) - " << frame.width
        <<"\nHeight of polygon frame rect after rotate(45) - " << frame.height;
    polygon->scale(2);
    std::cout << "\nPolygon area after scale(2) - " << polygon->getArea() << '\n';

    std::shared_ptr<anastasiev::Shape> rectangle
        = std::make_shared<anastasiev::Rectangle>(anastasiev::Rectangle(3, 5, {-100, 0}));
    std::cout << "\nRectangle area - " << rectangle->getArea() << '\n';
    frame = rectangle->getFrameRect();
    std::cout << "Width of rectangle frame rect - " << frame.width
        <<"\nHeight of rectangle frame rect - " << frame.height;
    rectangle->rotate(45);
    frame = rectangle->getFrameRect();
    std::cout << "\nRectangle area after rotate(45) - " << rectangle->getArea()
        << "\nWidth of rectangle frame rect after rotate(45) - " << frame.width
        <<"\nHeight of rectangle frame rect after rotate(45) - " << frame.height;
    rectangle->scale(2);
    std::cout << "\nRectangle area after scale(2) - " << rectangle->getArea() << '\n';

    std::shared_ptr<anastasiev::Shape> triangle
        = std::make_shared<anastasiev::Triangle>(anastasiev::Triangle({50, 50}, {50, 53},{54, 50}));
    std::cout << "\nTriangle area - " << triangle->getArea() << '\n';
    frame = triangle->getFrameRect();
    std::cout << "Width of triangle frame rect - " << frame.width
        <<"\nHeight of triangle frame rect - " << frame.height;
    triangle->rotate(45);
    frame = triangle->getFrameRect();
    std::cout << "\nTriangle area after rotate(45) - " << triangle->getArea()
        << "\nWidth of triangle frame rect after rotate(45) - " << frame.width
        <<"\nHeight of triangle frame rect after rotate(45) - " << frame.height;
    triangle->scale(2);
    std::cout << "\nTriangle area after scale(2) - " << triangle->getArea() << '\n';
    std::shared_ptr<anastasiev::Shape> circle
        = std::make_shared<anastasiev::Circle>(anastasiev::Circle(2, {3, 3}));
    anastasiev::Matrix matrix;
    matrix.addShape(polygon);
    matrix.addShape(rectangle);
    matrix.addShape(triangle);
    matrix.addShape(circle);
    std::cout << "\nShapes from first layer:\nPolygon area - " << matrix.getShape(0,0)->getArea()
        <<"\nRectangle area - " << matrix.getShape(0, 1)->getArea()
        <<"\nTriangle area - " << matrix.getShape(0, 2)->getArea()
        <<"\nShapes from second layer:\nCircle area - " << matrix.getShape(1,0)->getArea() << '\n';
    return 0;
  }
  catch(const std::exception & exc)
  {
    std::cerr << exc.what() << '\n';
    return -1;
  }
  catch(...)
  {
    std::cerr << "Unknown error!" << '\n';
    return -1;
  }
}
