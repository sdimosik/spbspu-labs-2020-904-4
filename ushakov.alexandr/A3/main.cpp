#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"

int main()
{
  try
  {
    ushakov::point_t point{2.0, 4.0};
    ushakov::Circle circle({0.0, 0.0}, 2.0);
    ushakov::Shape *shape = &circle;

    std::cout << "After creation: ";
    shape->print();
    std::cout << "Circle area: " << shape->getArea() << std::endl;
    shape->printFrameRectangle();

    shape->move(1.0, 2.0);
    std::cout << "After shifting by 1 in X axis and 2 in Y axis: ";
    shape->print();
    std::cout << "Circle area: " << shape->getArea() << std::endl;
    shape->printFrameRectangle();

    shape->move(point);
    std::cout << "After moving to the point (2, 4): ";
    shape->print();
    std::cout << "Circle area: " << shape->getArea() << std::endl;
    shape->printFrameRectangle();

    shape->scale(1.5);
    std::cout << "After scaling: ";
    shape->print();
    std::cout << "Circle area: " << shape->getArea() << std::endl;
    shape->printFrameRectangle();

    std::cout << std::endl;

    ushakov::Rectangle rectangle(2.0, 4.0, {3.0, 3.0});
    shape = &rectangle;

    std::cout << "After creation: ";
    shape->print();
    std::cout << "Rectangle area: " << shape->getArea() << std::endl;
    shape->printFrameRectangle();

    shape->move(1.0, 2.0);
    std::cout << "After shifting by 1 in X axis and 2 in Y axis: ";
    shape->print();
    std::cout << "Rectangle area: " << shape->getArea() << std::endl;
    shape->printFrameRectangle();

    shape->move(point);
    std::cout << "After moving to the point (2, 4): ";
    shape->print();
    std::cout << "Rectangle area: " << shape->getArea() << std::endl;
    shape->printFrameRectangle();

    shape->scale(2);
    std::cout << "After scaling: ";
    shape->print();
    std::cout << "Rectangle area: " << shape->getArea() << std::endl;
    shape->printFrameRectangle();

    std::cout << std::endl;

    ushakov::Triangle triangle({0.0, 0.0}, {0.0, 4.0}, {4.0, 0.0});
    shape = &triangle;

    std::cout << "After creation: ";
    shape->print();
    std::cout << "Triangle area: " << shape->getArea() << std::endl;
    shape->printFrameRectangle();

    shape->move(1.0, 2.0);
    std::cout << "After shifting by 1 in X axis and 2 in Y axis: ";
    shape->print();
    std::cout << "Triangle area: " << shape->getArea() << std::endl;
    shape->printFrameRectangle();

    shape->move(point);
    std::cout << "After moving to the point (2, 4): ";
    shape->print();
    std::cout << "Triangle area: " << shape->getArea() << std::endl;
    shape->printFrameRectangle();

    shape->scale(2.5);
    std::cout << "After scaling: ";
    shape->print();
    std::cout << "Triangle area: " << shape->getArea() << std::endl;
    shape->printFrameRectangle();

    std::cout << std::endl;

    ushakov::Rectangle rectangle2(3.1, 4.8, {0.4, 5.0});
    ushakov::Circle circle2({4.6, 7.0}, 5.0);
    ushakov::Triangle triangle2({0.0, 0.0}, {0.0, -4.0}, {-4.0, 0.0});

    std::shared_ptr<ushakov::Shape> shape1 = std::make_shared<ushakov::Rectangle>(rectangle);
    std::shared_ptr<ushakov::Shape> shape2 = std::make_shared<ushakov::Circle>(circle);
    std::shared_ptr<ushakov::Shape> shape3 = std::make_shared<ushakov::Triangle>(triangle);
    std::shared_ptr<ushakov::Shape> shape4 = std::make_shared<ushakov::Rectangle>(rectangle2);
    std::shared_ptr<ushakov::Shape> shape5 = std::make_shared<ushakov::Circle>(circle2);
    std::shared_ptr<ushakov::Shape> shape6 = std::make_shared<ushakov::Triangle>(triangle2);

    ushakov::CompositeShape compositeShape(6);

    compositeShape.addShape(shape1);
    compositeShape.addShape(shape2);
    compositeShape.addShape(shape3);
    compositeShape.addShape(shape4);
    compositeShape.addShape(shape5);
    compositeShape.addShape(shape6);

    ushakov::CompositeShape compositeShape2;

    compositeShape.print();
    compositeShape.printFrameRectangle();

    compositeShape.move(2.5, 1.0);
    std::cout << "After shifting in coordinates (2.5, 1.0):\n";
    compositeShape.print();
    compositeShape.printFrameRectangle();

    compositeShape.move({5.5, 7.0});
    std::cout << "After moving to the point (5.5, 7.0):\n";
    compositeShape.print();
    compositeShape.printFrameRectangle();

    std::cout << std::endl;

    compositeShape2 = compositeShape;
    std::cout << "Composite shape 2 before change:\n";
    compositeShape2.print();
    compositeShape.printFrameRectangle();

    compositeShape2.removeShape(1);
    std::cout << "After deleting 1 shape:\n";
    compositeShape2.print();

    compositeShape.printFrameRectangle();

    compositeShape2.scale(0.5);
    std::cout << "After scaling with coefficient 0.5:\n";
    compositeShape2.print();
    compositeShape.printFrameRectangle();
  }
  catch (const std::exception& err)
  {
    std::cerr << err.what() << std::endl;
    return -1;
  }
  catch (...)
  {
    std::cerr << "Error: Unknown error" << std::endl;
    return -2;
  }
  return 0;
}
