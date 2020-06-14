#define BOOST_TEST_MODULE myTest

#include <boost/test/included/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>
#include <memory>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

const double TOLERANCE_RANGE = 0.00001;
const double ANGLE = 45.0;

BOOST_AUTO_TEST_CASE(test_rotating_circle)
{
  bakaeva::Circle circle(5.0, {0.0, 0.0});
  const double area = circle.getArea();
  bakaeva::point_t center = circle.getCenter();
  circle.rotate(ANGLE);
  BOOST_CHECK_CLOSE(area, circle.getArea(), TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(center.x, circle.getCenter().x, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(center.y, circle.getCenter().y, TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_rotating_rectangle)
{
  bakaeva::Rectangle rectangle(4.0, 4.0, {0.0, 0.0});
  const double area = rectangle.getArea();
  bakaeva::point_t center = rectangle.getCenter();
  rectangle.rotate(ANGLE);
  BOOST_CHECK_CLOSE(rectangle.getAngle(), ANGLE, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(area, rectangle.getArea(), TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(center.x, rectangle.getCenter().x, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(center.y, rectangle.getCenter().y, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(rectangle.getCenter().x, rectangle.getFrameRect().pos.x, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(rectangle.getCenter().y, rectangle.getFrameRect().pos.y, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(4.0 * cos(ANGLE * M_PI / 180.0) * 2, rectangle.getFrameRect().width, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(4.0 * cos(ANGLE * M_PI / 180.0) * 2, rectangle.getFrameRect().height, TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_rotating_composite_shape)
{
  bakaeva::Rectangle rectangle(4.0, 2.0, {0.0, 0.0});
  bakaeva::Circle circle(1.0, {0.0, 2.0});
  bakaeva::CompositeShape::shapePtr shape1 = std::make_shared<bakaeva::Rectangle>(rectangle);
  bakaeva::CompositeShape::shapePtr shape2 = std::make_shared<bakaeva::Circle>(circle);
  bakaeva::CompositeShape compositeShape(2);
  compositeShape.addShape(shape1);
  compositeShape.addShape(shape2);
  bakaeva::point_t center = compositeShape.getCenter();
  double totalArea = compositeShape.getArea();
  compositeShape.rotate(2 * ANGLE);
  BOOST_CHECK_CLOSE(compositeShape.getCenter().x, center.x, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(compositeShape.getCenter().y, center.y, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), totalArea, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, 4.0, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, 4.0, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(compositeShape[0]->getCenter().x, 1.0, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(compositeShape[0]->getCenter().y, 1.0, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(compositeShape[1]->getCenter().x, -1.0, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(compositeShape[1]->getCenter().y, 1.0, TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_invalid_index_matrix)
{
  bakaeva::Matrix matrix;
  BOOST_CHECK_THROW(matrix[0], std::out_of_range);
  bakaeva::Circle circle(5, {0.0, 0.0});
  bakaeva::Matrix::shapePtr shape = std::make_shared<bakaeva::Circle>(circle);
  matrix.addShape(shape);
  BOOST_CHECK_THROW(matrix[0][1], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_pointer_added_shape)
{
  bakaeva::Matrix matrix;
  bakaeva::Matrix::shapePtr shape = nullptr;
  BOOST_CHECK_THROW(matrix.addShape(shape), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_copying_matrix)
{
  bakaeva::Rectangle rectangle(3.0, 4.8, {2.4, 3.0});
  bakaeva::Circle circle(5, {0.0, 0.0});
  bakaeva::Matrix::shapePtr shape1 = std::make_shared<bakaeva::Rectangle>(rectangle);
  bakaeva::Matrix::shapePtr shape2 = std::make_shared<bakaeva::Circle>(circle);
  bakaeva::Matrix matrix1;
  matrix1.addShape(shape1);
  matrix1.addShape(shape2);
  bakaeva::Matrix matrix2(matrix1);
  BOOST_CHECK(matrix2[0][0] == shape1);
  BOOST_CHECK(matrix2[1][0] == shape2);
  bakaeva::Matrix matrix3;
  matrix3 = matrix1;
  BOOST_CHECK(matrix3[0][0] == shape1);
  BOOST_CHECK(matrix3[1][0] == shape2);
}

BOOST_AUTO_TEST_CASE(test_moving_matrix)
{
  bakaeva::Rectangle rectangle(3.0, 4.8, {2.4, 3.0});
  bakaeva::Circle circle(5, {0.0, 0.0});
  bakaeva::Matrix::shapePtr shape1 = std::make_shared<bakaeva::Rectangle>(rectangle);
  bakaeva::Matrix::shapePtr shape2 = std::make_shared<bakaeva::Circle>(circle);
  bakaeva::Matrix matrix1;
  matrix1.addShape(shape1);
  matrix1.addShape(shape2);
  bakaeva::Matrix matrix2(std::move(matrix1));
  BOOST_CHECK(matrix2[0][0] == shape1);
  BOOST_CHECK(matrix2[1][0] == shape2);
  bakaeva::Matrix matrix3;
  matrix3 = std::move(matrix2);
  BOOST_CHECK(matrix3[0][0] == shape1);
  BOOST_CHECK(matrix3[1][0] == shape2);
}

BOOST_AUTO_TEST_CASE(test_adding_shapes)
{
  bakaeva::Rectangle rectangle(3.0, 4.8, {2.4, 3.0});
  bakaeva::Circle circle(5, {0.0, 0.0});
  bakaeva::Matrix::shapePtr shape1 = std::make_shared<bakaeva::Rectangle>(rectangle);
  bakaeva::Matrix::shapePtr shape2 = std::make_shared<bakaeva::Circle>(circle);
  bakaeva::Matrix matrix;
  matrix.addShape(shape1);
  matrix.addShape(shape2);
  BOOST_CHECK(matrix[0][0] == shape1);
  BOOST_CHECK(matrix[1][0] == shape2);
  BOOST_CHECK(matrix.getRows() == 2);
  BOOST_CHECK(matrix.getColumns() == 1);
}

BOOST_AUTO_TEST_CASE(test_layering_composite_shapes)
{
  bakaeva::Rectangle rectangle1(2.0, 4.0, {0.0, 0.0});
  bakaeva::Circle circle1(3.5, {0.5, 0.0});
  bakaeva::Rectangle rectangle2(2.1, 2.8, {7.0, 5.0});
  bakaeva::Circle circle2(2, {7.1, 4.6});

  bakaeva::CompositeShape::shapePtr shape1 = std::make_shared<bakaeva::Rectangle>(rectangle1);
  bakaeva::CompositeShape::shapePtr shape2 = std::make_shared<bakaeva::Circle>(circle1);
  bakaeva::CompositeShape::shapePtr shape3 = std::make_shared<bakaeva::Rectangle>(rectangle2);
  bakaeva::CompositeShape::shapePtr shape4 = std::make_shared<bakaeva::Circle>(circle2);

  bakaeva::CompositeShape compositeShape;
  compositeShape.addShape(shape1);
  compositeShape.addShape(shape2);
  compositeShape.addShape(shape3);
  compositeShape.addShape(shape4);

  bakaeva::Matrix matrix = compositeShape.layering();
  BOOST_CHECK(matrix.getRows() == 2);
  BOOST_CHECK(matrix.getColumns() == 2);
  BOOST_CHECK(matrix[0][0] == shape1);
  BOOST_CHECK(matrix[1][0] == shape2);
}
