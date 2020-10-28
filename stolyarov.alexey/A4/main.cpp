#include <iostream>
#include "base-types.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "polygon.hpp"
#include "matrix.hpp"

int main()
{
  try
  {
    stolyarov::Circle crcl(5, stolyarov::point_t{ 4.5, 1.3 });
    stolyarov::Shape* shape1 = &crcl;
    shape1->printInf();
    shape1->move(14.5, -2.1);
    shape1->printInf();
    shape1->move(stolyarov::point_t{ 3, 3 });
    shape1->printInf();
    shape1->printFrameInf();
    shape1->scale(2.4);
    shape1->printInf();
    shape1->rotate(123);
    shape1->printInf();
    shape1->printFrameInf();
    stolyarov::Rectangle rctngl(5, 2, stolyarov::point_t{ 3.2, 1.5 });
    stolyarov::Shape* shape2 = &rctngl;
    shape2->printInf();
    shape2->move(5.3, -4.1);
    shape2->printInf();
    shape2->move(stolyarov::point_t{ 2, 2 });
    shape2->printInf();
    shape2->printFrameInf();
    shape2->scale(0.7);
    shape2->printInf();
    shape2->rotate(123);
    shape2->printInf();
    shape2->printFrameInf();

    stolyarov::Circle crcl2(4, stolyarov::point_t{ 5.1, 3.1 });
    stolyarov::Rectangle rctngl2(2, 5, stolyarov::point_t{ 2.3, 5.1 });

    stolyarov::CompositeShape::shapePtr compShape1 = std::make_shared<stolyarov::Rectangle>(rctngl);
    stolyarov::CompositeShape::shapePtr compShape2 = std::make_shared<stolyarov::Circle>(crcl);
    stolyarov::CompositeShape::shapePtr compShape3 = std::make_shared<stolyarov::Rectangle>(rctngl2);
    stolyarov::CompositeShape::shapePtr compShape4 = std::make_shared<stolyarov::Circle>(crcl2);
    stolyarov::CompositeShape compositeShape;
    compositeShape.addElement(compShape1);
    compositeShape.addElement(compShape2);
    compositeShape.addElement(compShape3);
    compositeShape.addElement(compShape4);

    compositeShape.printInf();
    compositeShape.printFrameInf();
    compositeShape.move(2.4, 13.2);
    compositeShape.printInf();
    compositeShape.printFrameInf();
    compositeShape.scale(4.1);
    compositeShape.printInf();
    compositeShape.printFrameInf();
    compositeShape.removeElement(0);
    compositeShape.printInf();
    compositeShape.printFrameInf();
    compositeShape.rotate(30);
    compositeShape.printInf();
    compositeShape.printFrameInf();

    stolyarov::Matrix matrix;
    stolyarov::Rectangle rctngl3(2.1, 7.5, { 5.0, 5.0 });
    stolyarov::Circle crcl3(2.5, { 2.2, 2.2 });
    stolyarov::Rectangle rctngl4(1.3, 7.8, { 0.7, 0.5 });
    stolyarov::Circle crcl4(2.6, { 19.2, 19.2 });
    stolyarov::Rectangle rctngl5(1.0, 1.0, { 18.2, 18.2 });

    stolyarov::point_t point{ 1.2, 2.3 };
    stolyarov::point_t point1{ 2.1, 3.4 };
    stolyarov::point_t point2{ 3.4, 4.1 };
    stolyarov::point_t points[] = { point, point1, point2 };
    stolyarov::Polygon poly(points, 3);
    stolyarov::Shape* shape3 = &poly;
    shape3->printInf();
    shape3->printFrameInf();
    shape3->move(12.1, -5.1);
    shape3->printInf();
    shape3->printFrameInf();
    shape3->move(stolyarov::point_t{ 4.3, 8.1 });
    shape3->printInf();
    shape3->printFrameInf();
    shape3->scale(4.1);
    shape3->printInf();
    shape3->printFrameInf();
    shape3->rotate(234);
    shape3->printInf();
    shape3->printFrameInf();

    stolyarov::Matrix::shapePtr matrixShape1 = std::make_shared<stolyarov::Circle>(crcl);
    stolyarov::Matrix::shapePtr matrixShape2 = std::make_shared<stolyarov::Rectangle>(rctngl);
    stolyarov::Matrix::shapePtr matrixShape3 = std::make_shared<stolyarov::Circle>(crcl2);
    stolyarov::Matrix::shapePtr matrixShape4 = std::make_shared<stolyarov::Rectangle>(rctngl2);
    stolyarov::Matrix::shapePtr matrixShape5 = std::make_shared<stolyarov::Rectangle>(rctngl3);
    stolyarov::Matrix::shapePtr matrixShape6 = std::make_shared<stolyarov::Circle>(crcl3);
    stolyarov::Matrix::shapePtr matrixShape7 = std::make_shared<stolyarov::Rectangle>(rctngl4);
    stolyarov::Matrix::shapePtr matrixShape8 = std::make_shared<stolyarov::Circle>(crcl4);
    stolyarov::Matrix::shapePtr matrixShape9 = std::make_shared<stolyarov::Rectangle>(rctngl5);
    stolyarov::Matrix::shapePtr matrixShape10 = std::make_shared<stolyarov::Polygon>(poly);

    matrix.addElement(matrixShape1);
    matrix.addElement(matrixShape2);
    matrix.addElement(matrixShape3);
    matrix.addElement(matrixShape4);
    matrix.addElement(matrixShape5);
    matrix.addElement(matrixShape6);
    matrix.addElement(matrixShape7);
    matrix.addElement(matrixShape8);
    matrix.addElement(matrixShape9);
    matrix.addElement(matrixShape10);
    matrix.printInf();

    stolyarov::Matrix matrix1 = compositeShape.makeLayering();
    matrix1.printInf();
  }
  catch (const std::invalid_argument & message)
  {
    std::cerr << "ERROR: " << message.what() << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cerr << "ERROR: Unknown error";
    return 2;
  }
  return 0;
}
