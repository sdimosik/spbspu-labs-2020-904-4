#include <iostream>
#include <memory>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

int main()
{
  try
  {
    std::cout << " Shapes test:\n";
    bakaeva::Rectangle rectangle1(2.5, 4.0, {5.0, 5.0});
    bakaeva::Shape *shape = &rectangle1;
    std::cout << " Before change:\n";
    shape->printData();
    std::cout << "Rectangle area: " << shape->getArea() << '\n';

    shape->move(-3.0, 2.5);
    std::cout << " After shifting in coordinates:\n";
    shape->printData();
    std::cout << "Rectangle area: " << shape->getArea() << '\n';

    bakaeva::point_t point{3.25, -1.1};
    shape->move(point);
    std::cout << " After moving to the point:\n";
    shape->printData();
    std::cout << "Rectangle area: " << shape->getArea() << '\n';

    std::cout << " After scaling with coefficient 1.5:\n";
    shape->scale(1.5);
    shape->printData();
    std::cout << "Rectangle area: " << shape->getArea() << '\n';

    bakaeva::Circle circle1(4.0, {1.0, 4.7});
    shape = &circle1;
    std::cout << " Before change:\n";
    shape->printData();
    std::cout << "Circle area: " << shape->getArea() << '\n';
    shape->printFrameRect();

    shape->move(-2.0, 3.55);
    std::cout << " After shifting in coordinates:\n";
    shape->printData();
    std::cout << "Circle area: " << shape->getArea() << '\n';
    shape->printFrameRect();

    shape->move(point);
    std::cout << " After moving to the point:\n";
    shape->printData();
    std::cout << "Circle area: " << shape->getArea() << '\n';
    shape->printFrameRect();

    std::cout << " After scaling with coefficient 3.1:\n";
    shape->scale(3.1);
    shape->printData();
    std::cout << "Circle area: " << shape->getArea() << '\n';

    std::cout << "\n Composite shapes test:\n";
    bakaeva::Rectangle rectangle2(3.1, 4.8, {0.4, 5.0});
    bakaeva::Circle circle2(5, {4.6, 7.0});

    bakaeva::CompositeShape::shapePtr shape1 = std::make_shared<bakaeva::Rectangle>(rectangle1);
    bakaeva::CompositeShape::shapePtr shape2 = std::make_shared<bakaeva::Circle>(circle1);
    bakaeva::CompositeShape::shapePtr shape3 = std::make_shared<bakaeva::Rectangle>(rectangle2);
    bakaeva::CompositeShape::shapePtr shape4 = std::make_shared<bakaeva::Circle>(circle2);

    bakaeva::CompositeShape compositeShape(4);
    compositeShape.addShape(shape1);
    compositeShape.addShape(shape2);
    compositeShape.addShape(shape3);
    compositeShape.addShape(shape4);
    std::cout << " Composite shape 1 before change:\n";
    compositeShape.printData();

    compositeShape.move(2.5, 1.0);
    std::cout << " After shifting in coordinates (2.5, 1.0):\n";
    compositeShape.printData();

    compositeShape.move({5.5, 7.0});
    std::cout << " After moving to the point (5.5, 7.0):\n";
    compositeShape.printData();

    bakaeva::CompositeShape compositeShape2;
    compositeShape2 = compositeShape;
    std::cout << " Composite shape 2 before change:\n";
    compositeShape2.printData();

    compositeShape2.removeShape(1);
    std::cout << " After deleting 1 shape:\n";
    compositeShape2.printData();

    compositeShape2.scale(0.5);
    std::cout << " After scaling with coefficient 0.5:\n";
    compositeShape2.printData();

    std::cout << "\n Matrix test:\n";
    bakaeva::Matrix matrix;
    bakaeva::Rectangle rectangle3(3.1, 4.8, {0.0, 5.0});
    bakaeva::Circle circle3(3, {5.0, 10.0});
    bakaeva::Matrix::shapePtr shape5 = std::make_shared<bakaeva::Rectangle>(rectangle3);
    bakaeva::Matrix::shapePtr shape6 = std::make_shared<bakaeva::Circle>(circle3);
    bakaeva::Matrix::shapePtr shape7 = std::make_shared<bakaeva::CompositeShape>(compositeShape);
    matrix.addShape(shape5);
    matrix.addShape(shape6);
    matrix.addShape(shape7);
    matrix.printMatrix();
    matrix[0][1]->printData();
  }
  catch (const std::exception &exc)
  {
    std::cerr << exc.what() << std::endl;
    return -1;
  }
  catch (...)
  {
    std::cerr << "Unknown error!" << std::endl;
    return -1;
  }
  return 0;
}

