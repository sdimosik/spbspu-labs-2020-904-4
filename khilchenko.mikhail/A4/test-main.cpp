#define BOOST_TEST_MODULE test

#include <memory>
#include <boost/test/tools/floating_point_comparison.hpp>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

const double ACCURACY = 0.0001;

BOOST_AUTO_TEST_CASE(test_invalid_shape_matrix_add_shape)
{
  khilchenko::Matrix testMatrix;
  std::shared_ptr<khilchenko::Circle> circle = nullptr;
  BOOST_CHECK_THROW(testMatrix.addShape(circle), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_index_matrix_get_shape)
{
  khilchenko::Matrix testMatrix;
  BOOST_CHECK_THROW(testMatrix.getShape(23,23), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_rotate_circle)
{
  khilchenko::Circle circle(9, {0, 0});
  double startArea = circle.getArea();
  khilchenko::point_t startCenter = circle.getCenter();
  circle.rotate(36.2);
  BOOST_CHECK_CLOSE(startArea, circle.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(startCenter.x, circle.getCenter().x, ACCURACY);
  BOOST_CHECK_CLOSE(startCenter.y, circle.getCenter().y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rotate_rectangle)
{
  khilchenko::Rectangle rectangle(25, 5, {0, 0});
  double startArea = rectangle.getArea();
  khilchenko::point_t center = rectangle.getCenter();
  rectangle.rotate(72.3);
  BOOST_CHECK_CLOSE(startArea, rectangle.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(center.x, rectangle.getCenter().x, ACCURACY);
  BOOST_CHECK_CLOSE(center.y, rectangle.getCenter().y, ACCURACY);
  BOOST_CHECK_CLOSE(25 * cos(72.3 * M_PI / 180) + 5 * sin(72.3 * M_PI / 180), rectangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(5 * cos(72.3 * M_PI / 180) + 25 * sin(72.3 * M_PI / 180) , rectangle.getFrameRect().height, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rotate_composite_shape)
{
  khilchenko::CompositeShape compositeShape(2);
  std::shared_ptr<khilchenko::Shape> circle = std::make_shared<khilchenko::Circle>(khilchenko::Circle(9, {0, 0}));
  std::shared_ptr<khilchenko::Shape> rectangle = std::make_shared<khilchenko::Rectangle>(khilchenko::Rectangle(9, 10, {5, 25}));
  compositeShape.addShape(circle);
  compositeShape.addShape(rectangle);
  double startArea = compositeShape.getFrameRect().width * compositeShape.getFrameRect().height;
  compositeShape.rotate(65.9);
  BOOST_CHECK((compositeShape.getFrameRect().width * compositeShape.getFrameRect().height) != startArea);
}

BOOST_AUTO_TEST_CASE(test_add_one_shape_matrix)
{
  std::shared_ptr<khilchenko::Shape> circle = std::make_shared<khilchenko::Circle>(khilchenko::Circle(9, {0, 0}));
  khilchenko::Matrix matrix;
  matrix.addShape(circle);
  BOOST_CHECK(matrix.getAmountOfColoumns() == 1);
  BOOST_CHECK(matrix.getAmountOfRows() == 1);
}

BOOST_AUTO_TEST_CASE(test_add_two_not_overlapping_shapes_matrix)
{
  std::shared_ptr<khilchenko::Shape> circle = std::make_shared<khilchenko::Circle>(khilchenko::Circle(4.5, {0, 0}));
  std::shared_ptr<khilchenko::Shape> rectangle = std::make_shared<khilchenko::Rectangle>(khilchenko::Rectangle(6, 4, {10, 0}));
  khilchenko::Matrix matrix;
  matrix.addShape(circle);
  matrix.addShape(rectangle);
  BOOST_CHECK(matrix.getAmountOfColoumns() == 2);
  BOOST_CHECK(matrix.getAmountOfRows() == 1);
}

BOOST_AUTO_TEST_CASE(test_add_two_overlapping_shapes_matrix)
{
  std::shared_ptr<khilchenko::Shape> circle = std::make_shared<khilchenko::Circle>(khilchenko::Circle(9, {0, 0}));
  std::shared_ptr<khilchenko::Shape> rectangle = std::make_shared<khilchenko::Rectangle>(khilchenko::Rectangle(20, 5, {0, 0}));
  khilchenko::Matrix matrix;
  matrix.addShape(circle);
  matrix.addShape(rectangle);
  BOOST_CHECK(matrix.getAmountOfColoumns() == 1);
  BOOST_CHECK(matrix.getAmountOfRows() == 2);
}

BOOST_AUTO_TEST_CASE(test_add_three_overlapping_shapes_matrix)
{
  std::shared_ptr<khilchenko::Shape> circle1 = std::make_shared<khilchenko::Circle>(khilchenko::Circle(2, {0, 0}));
  std::shared_ptr<khilchenko::Shape> rectangle = std::make_shared<khilchenko::Rectangle>(khilchenko::Rectangle(20, 10, {4, 0}));
  std::shared_ptr<khilchenko::Shape> circle2 = std::make_shared<khilchenko::Circle>(khilchenko::Circle(2, {7, 0}));
  khilchenko::Matrix matrix;
  matrix.addShape(circle1);
  matrix.addShape(rectangle);
  matrix.addShape(circle2);
  BOOST_CHECK(matrix.getAmountOfColoumns() == 1);
  BOOST_CHECK(matrix.getAmountOfRows() == 3);
}

BOOST_AUTO_TEST_CASE(test_get_shape_matrix)
{
  khilchenko::Matrix matrix;
  std::shared_ptr<khilchenko::Shape> circle = std::make_shared<khilchenko::Circle>(khilchenko::Circle(4.5, {0, 0}));
  matrix.addShape(circle);
  std::shared_ptr<khilchenko::Shape> rectangle = std::make_shared<khilchenko::Rectangle>(khilchenko::Rectangle(6, 4, {10, 0}));
  matrix.addShape(rectangle);
  std::shared_ptr<khilchenko::Shape> rectangle1 = std::make_shared<khilchenko::Rectangle>(khilchenko::Rectangle(20, 5, {0, 0}));
  matrix.addShape(rectangle1);
  BOOST_CHECK(matrix.getShape(1,1) == nullptr);
  BOOST_CHECK(matrix.getShape(0,0) == circle);
  BOOST_CHECK(matrix.getShape(0,1) == rectangle);
  BOOST_CHECK(matrix.getShape(1,0) == rectangle1);
}

BOOST_AUTO_TEST_CASE(test_layer_matrix_in_composite_shape)
{
  std::shared_ptr<khilchenko::Shape> circle1 = std::make_shared<khilchenko::Circle>(khilchenko::Circle(2, {0, 0}));
  std::shared_ptr<khilchenko::Shape> rectangle = std::make_shared<khilchenko::Rectangle>(khilchenko::Rectangle(20, 10, {4, 0}));
  std::shared_ptr<khilchenko::Shape> circle2 = std::make_shared<khilchenko::Circle>(khilchenko::Circle(2, {7, 0}));
  khilchenko::CompositeShape compositeShape;
  compositeShape.addShape(circle1);
  compositeShape.addShape(rectangle);
  compositeShape.addShape(circle2);
  khilchenko::Matrix layerMatrix = compositeShape.getLayerMatrix();
  BOOST_CHECK(layerMatrix.getAmountOfColoumns() == 1);
  BOOST_CHECK(layerMatrix.getAmountOfRows() == 3);
}
