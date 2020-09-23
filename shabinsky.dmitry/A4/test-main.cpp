#define BOOST_TEST_MODULE shapetest

#include <cmath>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

const double ACCURACY_DOUBLE = 0.0001;

BOOST_AUTO_TEST_CASE(test_rotate_circle)
{
  shabinsky::Circle circle(10, {0, 0});
  shabinsky::rectangle_t rectangle = circle.getFrameRect();
  circle.rotate(56);
  BOOST_CHECK(circle.getFrameRect() == rectangle);
}

BOOST_AUTO_TEST_CASE(test_rotate_rectangle)
{
  shabinsky::Rectangle rectangle({0, 0}, 10, 10);
  shabinsky::rectangle_t rectangle1 = rectangle.getFrameRect();
  rectangle.rotate(90);
  BOOST_CHECK(rectangle.getFrameRect() == rectangle1);
}

BOOST_AUTO_TEST_CASE(test_rotate_composite_shape)
{
  shabinsky::CompositeShape compositeShape;
  std::shared_ptr<shabinsky::Shape> rect1 = std::make_shared<shabinsky::Rectangle>(shabinsky::Rectangle({1, 1}, 2, 2));
  std::shared_ptr<shabinsky::Shape> rect2 = std::make_shared<shabinsky::Rectangle>(shabinsky::Rectangle({11, 1}, 2, 2));
  std::shared_ptr<shabinsky::Shape> rect3 = std::make_shared<shabinsky::Rectangle>(shabinsky::Rectangle({4, 5}, 2, 2));
  compositeShape.addShape(rect1);
  compositeShape.addShape(rect2);
  compositeShape.addShape(rect3);
  compositeShape.rotate(90);
  shabinsky::rectangle_t rectangle1{6, 12, {6, 3}};
  BOOST_CHECK(compositeShape.getFrameRect() == rectangle1);
}

BOOST_AUTO_TEST_CASE(test_invalid_index_matrix)
{
  shabinsky::Matrix matrix;
  BOOST_CHECK_THROW(matrix[0], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_add_matrix)
{
  shabinsky::Matrix matrix;
  shabinsky::Matrix::shapePtr shape = nullptr;
  BOOST_CHECK_THROW(matrix.add(shape), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_index_removed_shape)
{
  shabinsky::Matrix matrix;
  BOOST_CHECK_THROW(matrix.remove(0, 0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_add_and_remove_shape)
{
  shabinsky::Rectangle rectangle({0, 0}, 10, 10);
  shabinsky::Circle circle(10, {0, 0});
  shabinsky::Matrix::shapePtr shape1 = std::make_shared<shabinsky::Rectangle>(rectangle);
  shabinsky::Matrix::shapePtr shape2 = std::make_shared<shabinsky::Circle>(circle);
  shabinsky::Matrix matrix;
  matrix.add(shape1);
  matrix.add(shape2);
  BOOST_CHECK(matrix[0][0] == shape1);
  BOOST_CHECK(matrix[1][0] == shape2);
  BOOST_CHECK(matrix.getRows() == 2);
  BOOST_CHECK(matrix.getColumns() == 1);
  matrix.remove(1, 0);
  BOOST_CHECK(matrix[1][0] == nullptr);
}
