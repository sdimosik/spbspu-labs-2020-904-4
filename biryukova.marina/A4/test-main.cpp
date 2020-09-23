#define BOOST_TEST_MODULE TEST_A4
#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

const double ACCURACY_DOUBLE = 0.0001;

BOOST_AUTO_TEST_CASE(correctRotateCircle)
{
  biryukova::Circle circle(biryukova::point_t{1.8, 4.2}, 8.1);
  const double radius = circle.getRadius();
  const biryukova::point_t centre = circle.getCentre();
  const double area = circle.getArea();
  const double angle = 30.0;
  circle.rotate(angle);
  BOOST_CHECK_CLOSE(circle.getRadius(), radius, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle.getCentre().x, centre.x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle.getCentre().y, centre.y, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle.getArea(), area, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(correctRotateRectangle)
{
  biryukova::Rectangle rectangle(biryukova::point_t{0.0, 0.0}, 1.0, 1.0);
  const double width = rectangle.getWidth();
  const double height = rectangle.getHeight();
  const biryukova::point_t centre = rectangle.getCentre();
  const double area = rectangle.getArea();
  const double angle = 90.0;
  rectangle.rotate(angle);
  const double newFrameRectWidth = sqrt((width * width) + (height * height));
  const double newFrameRectHeight = sqrt((width * width) + (height * height));
  BOOST_CHECK_CLOSE(rectangle.getWidth(), width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rectangle.getHeight(), height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rectangle.getCentre().x, centre.x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rectangle.getCentre().y, centre.y, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rectangle.getArea(), area, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, newFrameRectWidth, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, newFrameRectHeight, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, centre.x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, centre.y, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(correctRotateCompositeShape)
{
  const double centreX = 1.0;
  const double centreY = 1.0;
  biryukova::Circle circle(biryukova::point_t{centreX, centreY}, 1.0);
  biryukova::CompositeShape::shapePtr shape1 =
      std::make_shared<biryukova::Circle>(circle);
  biryukova::Rectangle rectangle(biryukova::point_t{centreX + 0.5, centreY + 0.5}, 1.0, 1.0);
  biryukova::CompositeShape::shapePtr shape2 =
      std::make_shared<biryukova::Rectangle>(rectangle);
  const double angle = -180.0;
  biryukova::CompositeShape shapes(2);
  shapes.insert(shape1);
  shapes.insert(shape2);
  const biryukova::rectangle_t frameRectShapes = shapes.getFrameRect();
  BOOST_CHECK_CLOSE(frameRectShapes.width, 2.0, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRectShapes.height, 2.0, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(shapes.getCentre().x, centreX, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(shapes.getCentre().y, centreY, ACCURACY_DOUBLE);
  shapes.rotate(angle);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().width, frameRectShapes.width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().height, frameRectShapes.height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(shapes.getCentre().x, centreX, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(shapes.getCentre().y, centreY, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(correctPartitionCompositeShape)
{
  biryukova::Circle circle1(biryukova::point_t{2.5, -1.5}, 1.0);
  biryukova::CompositeShape::shapePtr shape1 =
      std::make_shared<biryukova::Circle>(circle1);
  biryukova::Rectangle rectangle1(biryukova::point_t{3.5, -1.0}, 1.0, 1.0);
  biryukova::CompositeShape::shapePtr shape2 =
      std::make_shared<biryukova::Rectangle>(rectangle1);
  biryukova::CompositeShape compositeShape(2);
  compositeShape.insert(shape1);
  compositeShape.insert(shape2);
  biryukova::Circle circle2(biryukova::point_t{0.0, 0.0}, 1.0);
  biryukova::CompositeShape::shapePtr shape3 =
      std::make_shared<biryukova::Circle>(circle2);
  biryukova::Rectangle rectangle2(biryukova::point_t{1.0, 1.5}, 2.0, 2.0);
  biryukova::CompositeShape::shapePtr shape4 =
      std::make_shared<biryukova::Rectangle>(rectangle2);
  biryukova::CompositeShape::shapePtr shape5 =
      std::make_shared<biryukova::CompositeShape>(compositeShape);
  biryukova::CompositeShape shapes(3);
  shapes.insert(shape3);
  shapes.insert(shape4);
  shapes.insert(shape5);
  biryukova::Matrix matrix = shapes.partition();
  const size_t rows = 2;
  const size_t columns = 2;
  BOOST_CHECK_EQUAL(matrix.getRows(), rows);
  BOOST_CHECK_EQUAL(matrix.getColumns(), columns);
  BOOST_CHECK(matrix[0][0] == shape3);
  BOOST_CHECK(matrix[0][1] == shape5);
  BOOST_CHECK(matrix[1][0] == shape4);
}

BOOST_AUTO_TEST_CASE(invalidIndexMatrix)
{
  biryukova::Matrix matrix;
  biryukova::Circle circle(biryukova::point_t{2.5, -1.5}, 1.0);
  biryukova::CompositeShape::shapePtr shape1 =
      std::make_shared<biryukova::Circle>(circle);
  matrix.insert(shape1);
  BOOST_CHECK_THROW(matrix[1][0], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(testOfCopyingMatrix)
{
  biryukova::Matrix matrix;
  biryukova::Circle circle(biryukova::point_t{0.0, 0.0}, 1.0);
  biryukova::CompositeShape::shapePtr shape1 =
      std::make_shared<biryukova::Circle>(circle);
  biryukova::Rectangle rectangle(biryukova::point_t{3.5, -1.0}, 1.0, 1.0);
  biryukova::CompositeShape::shapePtr shape2 =
      std::make_shared<biryukova::Rectangle>(rectangle);
  matrix.insert(shape1);
  matrix.insert(shape2);
  BOOST_CHECK(matrix[0][0] == shape1);
  BOOST_CHECK(matrix[0][1] == shape2);
  biryukova::Matrix matrixCopy(matrix);
  BOOST_CHECK(matrixCopy[0][0] == shape1);
  BOOST_CHECK(matrixCopy[0][1] == shape2);
}

BOOST_AUTO_TEST_CASE(testOfMovingMatrix)
{
  biryukova::Matrix matrix;
  biryukova::Circle circle(biryukova::point_t{0.0, 0.0}, 1.0);
  biryukova::CompositeShape::shapePtr shape1 =
      std::make_shared<biryukova::Circle>(circle);
  biryukova::Rectangle rectangle(biryukova::point_t{3.5, -1.0}, 1.0, 1.0);
  biryukova::CompositeShape::shapePtr shape2 =
      std::make_shared<biryukova::Rectangle>(rectangle);
  matrix.insert(shape1);
  matrix.insert(shape2);
  BOOST_CHECK(matrix[0][0] == shape1);
  BOOST_CHECK(matrix[0][1] == shape2);
  biryukova::Matrix matrixMove = std::move(matrix);
  BOOST_CHECK(matrixMove[0][0] == shape1);
  BOOST_CHECK(matrixMove[0][1] == shape2);
}
