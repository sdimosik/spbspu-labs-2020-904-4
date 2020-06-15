#define BOOST_TEST_MODULE mytest
#include <memory>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

const double PERMISSIBLE_ACCURACY = 0.00001;
const double ANGLE = 30.0;


BOOST_AUTO_TEST_CASE(test_invalid_rotating_circle)
{
  bulanov::Circle circle(3.0, {1.0, 1.0});
  const double area = circle.getArea();
  bulanov::point_t center = circle.getCenter();
  circle.rotate(ANGLE);
  BOOST_CHECK_CLOSE(area, circle.getArea(), PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(center.x, circle.getCenter().x, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(center.y, circle.getCenter().y, PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_invalid_rotating_rectangle)
{
  bulanov::Rectangle rectangle({0.4, 5.0}, 3.0, 5.0);
  const double area = rectangle.getArea();
  bulanov::point_t center = rectangle.getCenter();
  rectangle.rotate(ANGLE);
  BOOST_CHECK_CLOSE(rectangle.getAngle(), ANGLE, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(area, rectangle.getArea(), PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(center.x, rectangle.getCenter().x, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(center.y, rectangle.getCenter().y, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(rectangle.getCenter().x, rectangle.getFrameRect().pos.x, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(rectangle.getCenter().y, rectangle.getFrameRect().pos.y, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(5.0 * sin(ANGLE * M_PI / 180.0) + 3.0 * cos(ANGLE * M_PI / 180.0), rectangle.getFrameRect().width,
                    PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(5.0 * cos(ANGLE * M_PI / 180.0) + 3.0 * sin(ANGLE * M_PI / 180.0), rectangle.getFrameRect().height,
                    PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_invalid_rotating_compositeShape)
{
  bulanov::CompositeShape compositeShape(2);
  bulanov::Circle circle(2.0, {1.0, 2.0});
  bulanov::Rectangle rectangle({8.0, 7.0}, 4.0, 2.0);
  bulanov::CompositeShape::shapePtr shape1 = std::make_shared<bulanov::Circle>(circle);
  bulanov::CompositeShape::shapePtr shape2 = std::make_shared<bulanov::Rectangle>(rectangle);
  compositeShape.addElement(shape1);
  compositeShape.addElement(shape2);
  bulanov::point_t center = compositeShape.getCenter();
  double commonArea = compositeShape.getArea();
  compositeShape.rotate(3 * ANGLE);
  BOOST_CHECK_CLOSE(compositeShape.getCenter().x, center.x, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getCenter().y, center.y, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), commonArea, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, 8.0, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, 11.0, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape[0]->getCenter().x, 6.5, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape[0]->getCenter().y, 0.5, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape[1]->getCenter().x, 1.5, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape[1]->getCenter().y, 7.5, PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_invalid_index_matrix)
{
  bulanov::Matrix matrix;
  BOOST_CHECK_THROW(matrix[0], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_added_shape)
{
  bulanov::Matrix matrix;
  bulanov::Matrix::shapePtr shape = nullptr;
  BOOST_CHECK_THROW(matrix.addElement(shape), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_copying_matrix_and_index_figure)
{
  bulanov::Rectangle rectangle({0.0, 0.0}, 10.0, 2.0);
  bulanov::Circle circle(2.0, {1.0, 2.0});
  bulanov::Matrix::shapePtr shape1 = std::make_shared<bulanov::Rectangle>(rectangle);
  bulanov::Matrix::shapePtr shape2 = std::make_shared<bulanov::Circle>(circle);
  bulanov::Matrix matrix1;
  matrix1.addElement(shape1);
  matrix1.addElement(shape2);
  bulanov::Matrix matrix2;
  matrix2 = matrix1;
  BOOST_CHECK(matrix2[0][0] == shape1);
  BOOST_CHECK(matrix2[1][0] == shape2);
  bulanov::Matrix matrix3(matrix1);
  BOOST_CHECK(matrix3[0][0] == shape1);
  BOOST_CHECK(matrix3[1][0] == shape2);
  BOOST_CHECK(matrix1.getLevels() == 2);
  BOOST_CHECK(matrix1.getColumns() == 1);

  bulanov::Rectangle rectangle2({10.0, 10.0}, 4.0, 2.0);
  bulanov::Circle circle2(1.0, {5.0, 1.0});
  bulanov::Matrix::shapePtr shape3 = std::make_shared<bulanov::Rectangle>(rectangle2);
  bulanov::Matrix::shapePtr shape4 = std::make_shared<bulanov::Circle>(circle2);
  matrix1.addElement(shape3);
  matrix1.addElement(shape4);
  BOOST_CHECK(matrix1[0][1] == shape3);
  BOOST_CHECK(matrix1[1][1] == shape4);
  BOOST_CHECK(matrix1.getLevels() == 2);
  BOOST_CHECK(matrix1.getColumns() == 2);

}

BOOST_AUTO_TEST_CASE(test_moving_matrix)
{
  bulanov::Rectangle rectangle({0.0, 0.0}, 4.0, 2.0);
  bulanov::Circle circle(2.0, {1.0, 2.0});
  bulanov::Matrix::shapePtr shape1 = std::make_shared<bulanov::Rectangle>(rectangle);
  bulanov::Matrix::shapePtr shape2 = std::make_shared<bulanov::Circle>(circle);
  bulanov::Matrix matrix1;
  matrix1.addElement(shape1);
  matrix1.addElement(shape2);
  bulanov::Matrix matrix2;
  matrix2 = std::move(matrix1);
  BOOST_CHECK(matrix2[0][0] == shape1);
  BOOST_CHECK(matrix2[1][0] == shape2);
  bulanov::Matrix matrix3(std::move(matrix2));
  BOOST_CHECK(matrix3[0][0] == shape1);
  BOOST_CHECK(matrix3[1][0] == shape2);
}

