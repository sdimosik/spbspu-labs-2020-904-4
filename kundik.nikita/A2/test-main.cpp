#define BOOST_TEST_MODULE Mytest

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "circle.hpp"
#include "rectangle.hpp"

const double ACCURACY = 0.00001;
const kundik::point_t coordinates = {15.0, 16.0};
const double circleRadius = 5.0;
const double rectangleHeight = 4.0;
const double rectangleWidth = 5.0;
const double moveX = 16.0;
const double moveY = 15.0;
const double negativeMoveX = -16.0;
const double negativeMoveY = -14.0;

BOOST_AUTO_TEST_CASE(test_valid_circle_after_mooving)
{
  kundik::Circle circle(coordinates, circleRadius);
  const kundik::rectangle_t frame = circle.getFrameRect();
  const double area = circle.getArea();
  circle.move(moveX, moveY);
  BOOST_CHECK_CLOSE(frame.height, circle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(frame.width, circle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(area, circle.getArea(), ACCURACY);
  circle.move(negativeMoveX, negativeMoveY);
  BOOST_CHECK_CLOSE(frame.height, circle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(frame.height, circle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(area, circle.getArea(), ACCURACY);
}
BOOST_AUTO_TEST_CASE(test_valid_rectangle_after_mooving)
{
  kundik::Rectangle rectangle(coordinates, rectangleHeight, rectangleWidth);
  const kundik::rectangle_t frame = rectangle.getFrameRect();
  const double area = rectangle.getArea();
  rectangle.move(moveX, moveY);
  BOOST_CHECK_CLOSE(frame.height, rectangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(frame.width, rectangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(area, rectangle.getArea(), ACCURACY);
  rectangle.move(negativeMoveX, negativeMoveY);
  BOOST_CHECK_CLOSE(frame.height, rectangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(frame.width, rectangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(area, rectangle.getArea(), ACCURACY);
}
BOOST_AUTO_TEST_CASE(test_circle_area_scale)
{
  kundik::Circle circle(coordinates, circleRadius);
  const double area = circle.getArea();
  circle.scale(2);
  BOOST_CHECK_CLOSE(area * 4, circle.getArea(), ACCURACY);
}
BOOST_AUTO_TEST_CASE(test_rectangle_area_scale)
{
  kundik::Rectangle rectangle(coordinates, rectangleHeight, rectangleWidth);
  const double area = rectangle.getArea();
  double coefficent = 2;
  rectangle.scale(coefficent);
  BOOST_CHECK_CLOSE(area * coefficent * coefficent, rectangle.getArea(), ACCURACY);
}
BOOST_AUTO_TEST_CASE(test_invalid_value_circle_radius)
{
  BOOST_CHECK_THROW(kundik::Circle(coordinates, -5.0), std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(test_invalid_value_rectangle_height)
{
  BOOST_CHECK_THROW(kundik::Rectangle(coordinates, -6.0, 5.0), std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(test_invalid_value_rectangle_width)
{
  BOOST_CHECK_THROW(kundik::Rectangle(coordinates, 6.0, -5.0), std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(test_invalid_value_circle_scale)
{
  kundik::Circle circle(coordinates, circleRadius);
  BOOST_CHECK_THROW(circle.scale(-2.0), std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(test_invalid_value_rectangle_scale)
{
  kundik::Rectangle rectangle(coordinates, rectangleHeight, rectangleWidth);
  BOOST_CHECK_THROW(rectangle.scale(-2.0), std::invalid_argument);
}
