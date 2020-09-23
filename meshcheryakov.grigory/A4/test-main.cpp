#define BOOST_TEST_MODULE LAB_A4

#include <boost/test/included/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>
#include <memory>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

const double ACCURACY = 0.00001;

BOOST_AUTO_TEST_CASE(test_empty_shape_add_shape)
{
  meshcheryakov::Matrix matrix;
  std::shared_ptr<meshcheryakov::Shape> shape = nullptr;
  BOOST_CHECK_THROW(matrix.addShape(shape), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_index_matrix)
{
  meshcheryakov::Matrix matrix;
  BOOST_CHECK_THROW(matrix[0], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_over_lapping_add_shapes)
{
  meshcheryakov::Matrix matrix;
  meshcheryakov::Circle circle(3, {1.0, 1.0});
  std::shared_ptr<meshcheryakov::Shape> shape1 = std::make_shared<meshcheryakov::Circle>(circle);
  matrix.addShape(shape1);
  meshcheryakov::Rectangle rectangle({5.0, 5.0, {0.0, 0.0}});
  std::shared_ptr<meshcheryakov::Shape> shape2 = std::make_shared<meshcheryakov::Rectangle>(rectangle);
  matrix.addShape(shape2);
  BOOST_CHECK(matrix[0][0] == shape1);
  BOOST_CHECK(matrix[1][0] == shape2);
  BOOST_CHECK(matrix.getRows() == 2);
  BOOST_CHECK(matrix.getColumns() == 1);
}

BOOST_AUTO_TEST_CASE(test_not_over_lapping_add_shapes)
{
  meshcheryakov::Matrix matrix;
  meshcheryakov::Circle circle(3, {1.0, 1.0});
  std::shared_ptr<meshcheryakov::Shape> shape1 = std::make_shared<meshcheryakov::Circle>(circle);
  matrix.addShape(shape1);
  meshcheryakov::Rectangle rectangle({5.0, 5.0, {10.0, 10.0}});
  std::shared_ptr<meshcheryakov::Shape> shape2 = std::make_shared<meshcheryakov::Rectangle>(rectangle);
  matrix.addShape(shape2);
  BOOST_CHECK(matrix[0][0] == shape1);
  BOOST_CHECK(matrix[0][1] == shape2);
  BOOST_CHECK(matrix.getRows() == 1);
  BOOST_CHECK(matrix.getColumns() == 2);
}

BOOST_AUTO_TEST_CASE(test_rotate_circle)
{
  meshcheryakov::Circle circle(3.0, {0.0, 0.0});
  const double area = circle.getArea();
  meshcheryakov::point_t center = circle.getPosition();
  circle.rotate(40.0);
  BOOST_CHECK_CLOSE(area, circle.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(center.x, circle.getPosition().x, ACCURACY);
  BOOST_CHECK_CLOSE(center.y, circle.getPosition().y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rotate_rectangle)
{
  meshcheryakov::Rectangle rectangle({3.0, 3.0, {0.0, 0.0}});
  const double area = rectangle.getArea();
  meshcheryakov::point_t center = rectangle.getPosition();
  rectangle.rotate(45);
  BOOST_CHECK_CLOSE(rectangle.getArea(), area, ACCURACY);
  BOOST_CHECK_CLOSE(area, rectangle.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(center.x, rectangle.getPosition().x, ACCURACY);
  BOOST_CHECK_CLOSE(center.y, rectangle.getPosition().y, ACCURACY);
  BOOST_CHECK_CLOSE(45, rectangle.getAngle(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rotate_composite_shape)
{
  meshcheryakov::CompositeShape compositeShape(2);
  meshcheryakov::Circle circle(2.0, {2.0, 2.0});
  std::shared_ptr<meshcheryakov::Shape> shape1 = std::make_shared<meshcheryakov::Circle>(circle);
  compositeShape.addShape(shape1);
  meshcheryakov::Rectangle rectangle({4.0, 2.0, {4.0, 2.0}});
  std::shared_ptr<meshcheryakov::Shape> shape2 = std::make_shared<meshcheryakov::Rectangle>(rectangle);
  compositeShape.addShape(shape2);

  double area = compositeShape.getArea();
  compositeShape.rotate(90);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), area, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, 6.0, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, 5.0, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape[0]->getPosition().x, 4.5, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape[0]->getPosition().y, 3.5, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape[1]->getPosition().x, 6.5, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape[1]->getPosition().y, 5.5, ACCURACY);
}
