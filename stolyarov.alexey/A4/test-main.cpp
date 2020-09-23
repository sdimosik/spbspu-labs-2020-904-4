#define BOOST_TEST_MODULE A4test

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "../common/composite-shape.hpp"
#include "../common/circle.hpp"
#include "../common/rectangle.hpp"
#include "../common/polygon.hpp"

const double ACCURACY = 0.0000001;

BOOST_AUTO_TEST_CASE(test_circle_valid_rotate)
{
  stolyarov::Circle circle(4.5, { 0, 0 });
  const double area = circle.getArea();
  stolyarov::point_t pos = circle.getCenter();
  circle.rotate(30);
  BOOST_CHECK_CLOSE(area, circle.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(pos.x, circle.getCenter().x, ACCURACY);
  BOOST_CHECK_CLOSE(pos.y, circle.getCenter().y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rectangle_valid_rotate)
{
  stolyarov::Rectangle rectangle(12.1, 23.1, { 0, 0 });
  const double area = rectangle.getArea();
  stolyarov::point_t pos = rectangle.getCenter();
  const double width = rectangle.getFrameRect().width;
  const double height = rectangle.getFrameRect().height;
  rectangle.rotate(90);
  BOOST_CHECK_CLOSE(area, rectangle.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(pos.x, rectangle.getCenter().x, ACCURACY);
  BOOST_CHECK_CLOSE(pos.y, rectangle.getCenter().y, ACCURACY);
  BOOST_CHECK_CLOSE(width, rectangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(height, rectangle.getFrameRect().width, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_valid_rotate)
{
  stolyarov::CompositeShape compShape;
  std::shared_ptr<stolyarov::Shape> rectangle1
    = std::make_shared<stolyarov::Rectangle>(stolyarov::Rectangle(32.1, 4.5, { 3.5, 2.5 }));
  std::shared_ptr<stolyarov::Shape> rectangle2
    = std::make_shared<stolyarov::Rectangle>(stolyarov::Rectangle(32.1, 4.5, { 6.5, 2.5 }));
  compShape.addElement(rectangle1);
  compShape.addElement(rectangle2);
  const double area = compShape.getArea();
  stolyarov::point_t pos = compShape.getFrameRect().pos;
  const double width = compShape.getFrameRect().width;
  const double height = compShape.getFrameRect().height;
  compShape.rotate(90);
  BOOST_CHECK_CLOSE(area, compShape.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(pos.x, compShape.getFrameRect().pos.x, ACCURACY);
  BOOST_CHECK_CLOSE(pos.y, compShape.getFrameRect().pos.y, ACCURACY);
  BOOST_CHECK_CLOSE(width, compShape.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(height, compShape.getFrameRect().width, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_polygon_invalid_constructor_argument)
{
  stolyarov::point_t point{ 1.1, 1.1 };
  stolyarov::point_t point1{ 0, 0 };
  stolyarov::point_t point2{ -1.1, 0 };
  stolyarov::point_t point3{ 0, -1.1 };
  stolyarov::point_t point4{ 0, 24.1 };
  stolyarov::point_t points[] = { point };
  BOOST_CHECK_THROW(stolyarov::Polygon poly(points, 1), std::invalid_argument);
  stolyarov::point_t points1[] = { point, point1, point2, point3 };
  BOOST_CHECK_THROW(stolyarov::Polygon poly(points1, 4), std::invalid_argument);
  stolyarov::point_t points2[] = { point1, point3, point4 };
  BOOST_CHECK_THROW(stolyarov::Polygon poly(points2, 3), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_polygon_invalid_argument_scale)
{
  stolyarov::point_t point1{ 0, 0 };
  stolyarov::point_t point2{ -1.1, 0 };
  stolyarov::point_t point3{ 0, -1.1 };
  stolyarov::point_t points[] = { point1, point2, point3 };
  stolyarov::Polygon poly(points, 3);
  BOOST_CHECK_THROW(poly.scale(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_polygon_valid_scale)
{
  stolyarov::point_t point{ -2.0, 3.0 };
  stolyarov::point_t point1{ -2.0, -5.0 };
  stolyarov::point_t point2{ 2.0, -5.0 };
  stolyarov::point_t point3{ 2.0, 3.0 };
  stolyarov::point_t points[] = { point, point1, point2, point3 };
  stolyarov::Polygon poly(points, 4);
  const double area = poly.getArea();
  const double rate = 2;
  poly.scale(rate);
  BOOST_CHECK_CLOSE(area * rate * rate, poly.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_polygon_valid_rotate)
{
  stolyarov::point_t point1{ 0, 0 };
  stolyarov::point_t point2{ -1.1, 0 };
  stolyarov::point_t point3{ 0, -1.1 };
  stolyarov::point_t points[] = { point1, point2, point3 };
  stolyarov::Polygon poly(points, 3);
  const double area = poly.getArea();
  stolyarov::point_t pos = poly.getCenter();
  const double width = poly.getFrameRect().width;
  const double height = poly.getFrameRect().height;
  poly.rotate(90);
  BOOST_CHECK_CLOSE(area, poly.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(pos.x, poly.getCenter().x, ACCURACY);
  BOOST_CHECK_CLOSE(pos.y, poly.getCenter().y, ACCURACY);
  BOOST_CHECK_CLOSE(width, poly.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(height, poly.getFrameRect().width, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_matrix_invalid_null_pointer_shape)
{
  stolyarov::Matrix matrix;
  BOOST_CHECK_THROW(matrix.addElement(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_index_matrix)
{
  stolyarov::Matrix matrix;
  BOOST_CHECK_THROW(matrix[0], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test__matrix_copying_and_index_figure)
{
  stolyarov::Rectangle rectangle(10.0, 2.0, { 0.0, 0.0 });
  stolyarov::Circle circle(2.0, { 1.0, 2.0 });
  stolyarov::Matrix::shapePtr shape1 = std::make_shared<stolyarov::Rectangle>(rectangle);
  stolyarov::Matrix::shapePtr shape2 = std::make_shared<stolyarov::Circle>(circle);
  stolyarov::Matrix matrix1;
  matrix1.addElement(shape1);
  matrix1.addElement(shape2);
  stolyarov::Matrix matrix2;
  matrix2 = matrix1;
  BOOST_CHECK(matrix2[0][0] == shape1);
  BOOST_CHECK(matrix2[1][0] == shape2);
  stolyarov::Matrix matrix3(matrix1);
  BOOST_CHECK(matrix3[0][0] == shape1);
  BOOST_CHECK(matrix3[1][0] == shape2);
  BOOST_CHECK(matrix1.getLevels() == 2);
  BOOST_CHECK(matrix1.getColumns() == 1);

  stolyarov::Rectangle rectangle2( 4.0, 2.0, { 10.0, 10.0 });
  stolyarov::Circle circle2(1.0, { 5.0, 1.0 });
  stolyarov::Matrix::shapePtr shape3 = std::make_shared<stolyarov::Rectangle>(rectangle2);
  stolyarov::Matrix::shapePtr shape4 = std::make_shared<stolyarov::Circle>(circle2);
  matrix1.addElement(shape3);
  matrix1.addElement(shape4);
  BOOST_CHECK(matrix1[0][1] == shape3);
  BOOST_CHECK(matrix1[1][1] == shape4);
  BOOST_CHECK(matrix1.getLevels() == 2);
  BOOST_CHECK(matrix1.getColumns() == 2);

}

BOOST_AUTO_TEST_CASE(test_matrix_valid_move)
{
  stolyarov::Rectangle rectangle(4.0, 2.0, { 0.0, 0.0 });
  stolyarov::Circle circle(2.0, { 1.0, 2.0 });
  stolyarov::Matrix::shapePtr shape1 = std::make_shared<stolyarov::Rectangle>(rectangle);
  stolyarov::Matrix::shapePtr shape2 = std::make_shared<stolyarov::Circle>(circle);
  stolyarov::Matrix matrix1;
  matrix1.addElement(shape1);
  matrix1.addElement(shape2);
  stolyarov::Matrix matrix2;
  matrix2 = std::move(matrix1);
  BOOST_CHECK(matrix2[0][0] == shape1);
  BOOST_CHECK(matrix2[1][0] == shape2);
  stolyarov::Matrix matrix3(std::move(matrix2));
  BOOST_CHECK(matrix3[0][0] == shape1);
  BOOST_CHECK(matrix3[1][0] == shape2);
}

