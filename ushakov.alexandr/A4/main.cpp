#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"
#include "polygon.hpp"

int main()
{
  try
  {
    ushakov::point_t point{2.0, 4.0};
    ushakov::Circle circle({0.0, 0.0}, 2.0);
    ushakov::Shape *shape = &circle;

    std::cout << "After creation: ";
    shape->print();
    shape->printFrameRectangle();
    std::cout << std::endl;

    shape->move(1.0, 2.0);
    std::cout << "After shifting by 1 in X axis and 2 in Y axis: ";
    shape->print();
    shape->printFrameRectangle();
    std::cout << std::endl;

    shape->move(point);
    std::cout << "After moving to the point (2, 4): ";
    shape->print();
    shape->printFrameRectangle();
    std::cout << std::endl;

    shape->scale(1.5);
    std::cout << "After scaling: ";
    shape->print();
    shape->printFrameRectangle();
    std::cout << std::endl;

    ushakov::Rectangle rectangle(2.0, 4.0, {3.0, 3.0});
    shape = &rectangle;

    std::cout << "After creation: ";
    shape->print();
    shape->printFrameRectangle();
    std::cout << std::endl;

    shape->move(1.0, 2.0);
    std::cout << "After shifting by 1 in X axis and 2 in Y axis: ";
    shape->print();
    shape->printFrameRectangle();
    std::cout << std::endl;

    shape->move(point);
    std::cout << "After moving to the point (2, 4): ";
    shape->print();
    shape->printFrameRectangle();
    std::cout << std::endl;

    shape->scale(2);
    std::cout << "After scaling: ";
    shape->print();
    shape->printFrameRectangle();
    std::cout << std::endl;

    ushakov::Triangle triangle({0.0, 0.0}, {0.0, 4.0}, {4.0, 0.0});
    shape = &triangle;

    std::cout << "After creation: ";
    shape->print();
    shape->printFrameRectangle();
    std::cout << std::endl;

    shape->move(1.0, 2.0);
    std::cout << "After shifting by 1 in X axis and 2 in Y axis: ";
    shape->print();
    shape->printFrameRectangle();
    std::cout << std::endl;

    shape->move(point);
    std::cout << "After moving to the point (2, 4): ";
    shape->print();
    shape->printFrameRectangle();
    std::cout << std::endl;

    shape->scale(2.5);
    std::cout << "After scaling: ";
    shape->print();
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
    std::cout << "Frame rectangle for this shape: ";
    compositeShape.printFrameRectangle();
    std::cout << std::endl;

    compositeShape.move(2.5, 1.0);
    std::cout << "After shifting in coordinates (2.5, 1.0):\n";
    compositeShape.print();
    compositeShape.printFrameRectangle();
    std::cout << std::endl;

    compositeShape.move({5.5, 7.0});
    std::cout << "After moving to the point (5.5, 7.0):\n";
    compositeShape.print();
    compositeShape.printFrameRectangle();
    std::cout << std::endl;

    compositeShape2 = compositeShape;

    std::shared_ptr<ushakov::Shape> shape7;
    shape7 = std::make_shared<ushakov::Polygon>(ushakov::Polygon({{2.0, 2.0}, {2.0, 5.0}, {5.0, 5.0}, {5.0, 2.0}}));

    compositeShape2.addShape(shape7);

    std::cout << std::endl;
    std::cout << "Rectangle frame rectangle area: " << shape1->getFrameRect().height * shape1->getFrameRect().width
        << std::endl;
    std::cout << "Circle frame rectangle area: " << shape2->getFrameRect().height * shape2->getFrameRect().width
        << std::endl;
    std::cout << "Triangle frame rectangle area: " << shape3->getFrameRect().height * shape3->getFrameRect().width
        << std::endl;
    std::cout << "Rectangle2 frame rectangle area: " << shape4->getFrameRect().height * shape4->getFrameRect().width
        << std::endl;
    std::cout << "Circle2 frame rectangle area: " << shape5->getFrameRect().height * shape5->getFrameRect().width
        << std::endl;
    std::cout << "Triangle2 frame rectangle area: " << shape6->getFrameRect().height * shape6->getFrameRect().width
        << std::endl;
    std::cout << "Polygon frame rectangle area: " << shape7->getFrameRect().height * shape7->getFrameRect().width
        << std::endl;
    std::cout << "Total composite shape frame rectangle area: "
        << compositeShape2.getFrameRect().height * compositeShape2.getFrameRect().width << std::endl;
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "Rectangle area: " << shape1->getArea() << std::endl;
    std::cout << "Circle area: " << shape2->getArea() << std::endl;
    std::cout << "Triangle area: " << shape3->getArea() << std::endl;
    std::cout << "Rectangle2 area: " << shape4->getArea() << std::endl;
    std::cout << "Circle2 area: " << shape5->getArea() << std::endl;
    std::cout << "Triangle2 area: " << shape6->getArea() << std::endl;
    std::cout << "Polygon area: " << shape7->getArea() << std::endl;
    std::cout << "Total composite shape area: " << compositeShape2.getArea() << std::endl;
    std::cout << std::endl;

    compositeShape2.print();
    compositeShape.printFrameRectangle();
    std::cout << std::endl;

    compositeShape2.removeShape(1);
    std::cout << "After removing circle from compositeShape 2:" << std::endl;
    compositeShape2.print();
    compositeShape.printFrameRectangle();
    std::cout << std::endl;

    compositeShape2.scale(0.5);
    std::cout << "After scaling with coefficient 0.5:" << std::endl;
    compositeShape2.print();
    compositeShape.printFrameRectangle();
    std::cout << std::endl;

    std::shared_ptr<ushakov::Shape> compositeShape_ptr = std::make_shared<ushakov::CompositeShape>(compositeShape);
    std::cout << "Adding Composite Shape into Composite Shape 2" << std::endl;
    compositeShape2.addShape(compositeShape_ptr);
    std::cout << "Composite shape 2 size: " << compositeShape2.getSize() << std::endl;

    std::cout << "Create matrix from Composite Shape 2" << std::endl;
    ushakov::Matrix matrix = compositeShape2.divide();

    std::cout << std::endl;
    matrix.print();
  }
  catch (const std::invalid_argument& err)
  {
    std::cerr << err.what() << std::endl;
    return -1;
  }
  catch (const std::exception& err)
  {
    std::cerr << err.what() << std::endl;
    return -2;
  }
  catch (...)
  {
    std::cerr << "Error: Unknown error" << std::endl;
    return -2;
  }

  return 0;
}
