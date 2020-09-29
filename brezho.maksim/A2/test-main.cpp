#define BOOST_TEST_MODULE mytest

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

const double PERMISSIBLE_ACCURACY = 0.00001;

BOOST_AUTO_TEST_CASE(test_invalid_argument_width_rectangle_constructor)
{
  BOOST_CHECK_THROW(brezho::Rectangle rectangle({ 0.0, 0.0 }, -1.0, 1.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_height_rectangle_constructor)
{
  BOOST_CHECK_THROW(brezho::Rectangle rectangle({ 0.0, 0.0 }, 1.0, 0.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_scaling_coefficient_rectangle)
{
  brezho::Rectangle rectangle({ 0.0, 0.0 }, 1.0, 1.0);
  BOOST_CHECK_THROW(rectangle.scale(-6.5), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_permanency_size_rectangle_moving)
{
  brezho::Rectangle rectangle({ 0.0, 0.0 }, 1.0, 1.0);
  const double area = rectangle.getArea();
  brezho::rectangle_t frameRect = rectangle.getFrameRect();

  rectangle.move(17.6, 18.4);
  BOOST_CHECK_CLOSE(frameRect.width, rectangle.getFrameRect().width, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.height, rectangle.getFrameRect().height, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(area, rectangle.getArea(), PERMISSIBLE_ACCURACY);

  rectangle.move({ -17.6, 18.4 });
  BOOST_CHECK_CLOSE(frameRect.width, rectangle.getFrameRect().width, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.height, rectangle.getFrameRect().height, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(area, rectangle.getArea(), PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_quadratic_change_area_rectangle)
{
  brezho::Rectangle rectangle({ 0.0, 0.0 }, 1.0, 1.0);
  const double area = rectangle.getArea();
  const double coef = 6.5;
  rectangle.scale(coef);
  BOOST_CHECK_CLOSE(area * coef * coef, rectangle.getArea(), PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_radius_circle_constructor)
{
  BOOST_CHECK_THROW(brezho::Circle circle({ 0.0, 0.0 }, -6.5), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_radius_circle_set)
{
  brezho::Circle circle({ 0.0, 0.0 }, 6.5);
  BOOST_CHECK_THROW(circle.setRadius(-4.6), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_scaling_coefficient_circle)
{
  brezho::Circle circle({ 0.0, 0.0 }, 6.5);
  BOOST_CHECK_THROW(circle.scale(-6.5), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_permanency_size_circle_moving)
{
  brezho::Circle circle({ 0.0, 0.0 }, 6.5);
  const double area = circle.getArea();
  const brezho::rectangle_t frameRect = circle.getFrameRect();

  circle.move(17.6, 18.4);
  BOOST_CHECK_CLOSE(frameRect.width, circle.getFrameRect().width, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.height, circle.getFrameRect().height, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(area, circle.getArea(), PERMISSIBLE_ACCURACY);

  circle.move({ -17.6, 18.4 });
  BOOST_CHECK_CLOSE(frameRect.width, circle.getFrameRect().width, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.height, circle.getFrameRect().height, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(area, circle.getArea(), PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_quadratic_change_area_circle)
{
  brezho::Circle circle({ 0.0, 0.0 }, 6.5);
  const double area = circle.getArea();
  const double coef = 6.5;
  circle.scale(coef);
  BOOST_CHECK_CLOSE(area * coef * coef, circle.getArea(), PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_identical_points_triangle_constructor)
{
  BOOST_CHECK_THROW(brezho::Triangle triangle({ 3.0, 4.0 }, { 3.0, 4.0 }, { 3.0, 0.0 }) , std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_points_on_one_line_triangle_constructor)
{
  BOOST_CHECK_THROW(brezho::Triangle triangle({ 0.0, 4.0 }, { 0.0, 5.0 }, { 0.0, 6.0 }), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_scaling_coefficient_triangle)
{
  brezho::Triangle triangle({ 3.0, 4.0 }, { 0.0, 4.0 }, { 3.0, 0.0 });
  BOOST_CHECK_THROW(triangle.scale(-6.5), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_permanency_size_triangle_moving)
{
  brezho::Triangle triangle({ 3.0, 4.0 }, { 0.0, 4.0 }, { 3.0, 0.0 });
  const double area = triangle.getArea();
  brezho::rectangle_t frameRect = triangle.getFrameRect();

  triangle.move(17.6, 18.4);
  BOOST_CHECK_CLOSE(frameRect.width, triangle.getFrameRect().width, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.height, triangle.getFrameRect().height, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(area, triangle.getArea(), PERMISSIBLE_ACCURACY);

  triangle.move({ -17.6, 18.4 });
  BOOST_CHECK_CLOSE(frameRect.width, triangle.getFrameRect().width, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.height, triangle.getFrameRect().height, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(area, triangle.getArea(), PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_quadratic_change_area_triangle)
{
  brezho::Rectangle rectangle({ 0.0, 0.0 }, 1.0, 1.0);
  const double area = rectangle.getArea();
  const double coef = 6.5;
  rectangle.scale(coef);
  BOOST_CHECK_CLOSE(area * coef * coef, rectangle.getArea(), PERMISSIBLE_ACCURACY);
}
