#define BOOST_TEST_MODULE shapetest

#include <cmath>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "rectangle.hpp"
#include "circle.hpp"

const double ACCURACY_DOUBLE = 0.0001;

BOOST_AUTO_TEST_CASE(test_invalid_argument_rectangle)
{
  BOOST_CHECK_THROW(shabinsky::Rectangle rect({75.0, 76.0}, -10.0, 13.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_rectangle_scale)
{
  shabinsky::Rectangle rect({75.0, 76.0}, 10.0, 13.0);
  BOOST_CHECK_THROW(rect.scale(-1.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_permanency_move_rectange)
{
  shabinsky::Rectangle rect({75.0, 76.0}, 10.0, 13.0);
  const shabinsky::rectangle_t frameRect = rect.getFrameRect();
  const double area = rect.getArea();
  rect.move({10.0, 10.0});
  BOOST_CHECK_CLOSE(frameRect.height, rect.getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.width, rect.getFrameRect().width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(area, rect.getArea(), ACCURACY_DOUBLE);
  rect.move(10.0, 10.0);
  BOOST_CHECK_CLOSE(frameRect.height, rect.getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.width, rect.getFrameRect().width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(area, rect.getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_correct_move_rectangle)
{
  shabinsky::Rectangle rect({75.0, 76.0}, 10.0, 13.0);
  const double x = -85.0,
    y = 10.0,
    oldX = rect.getPosition().x,
    oldY = rect.getPosition().y;
  rect.move(x, y);
  BOOST_CHECK_CLOSE(rect.getPosition().x, x + oldX, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rect.getPosition().y, y + oldY, ACCURACY_DOUBLE);
  rect.move({x, y});
  BOOST_CHECK_CLOSE(rect.getPosition().x, x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rect.getPosition().y, y, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_scale_rectangle_area)
{
  shabinsky::Rectangle rect({75.0, 76.0}, 10.0, 13.0);
  double w1 = rect.getWidth(), h1 = rect.getHeight();
  const double area_rect = rect.getArea(),
    scale = 1.5;
  rect.scale(scale);
  w1 = rect.getWidth(), h1 = rect.getHeight();
  const double area_rect1 = rect.getArea();
  BOOST_CHECK_CLOSE(area_rect * scale * scale, rect.getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_circle)
{
  BOOST_CHECK_THROW(shabinsky::Circle circle(-13.0, {75.0, 76.0}), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_circle_scale)
{
  shabinsky::Circle circle(13.0, {75.0, 76.0});
  BOOST_CHECK_THROW(circle.scale(-1.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_permanency_move_circle)
{
  shabinsky::Circle circle(13.0, {75.0, 76.0});
  const shabinsky::rectangle_t frameRect = circle.getFrameRect();
  const double area = circle.getArea();
  circle.move({10.0, 10.0});
  BOOST_CHECK_CLOSE(frameRect.height, circle.getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.width, circle.getFrameRect().width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(area, circle.getArea(), ACCURACY_DOUBLE);
  circle.move(10, 10);
  BOOST_CHECK_CLOSE(frameRect.height, circle.getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.width, circle.getFrameRect().width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(area, circle.getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_correct_move_circle)
{
  shabinsky::Circle circle(13.0, {75.0, 76.0});
  const double x = -85.0,
    y = 10.0,
    oldX = circle.getPosition().x,
    oldY = circle.getPosition().y;
  circle.move(x, y);
  BOOST_CHECK_CLOSE(circle.getPosition().x, x + oldX, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle.getPosition().y, y + oldY, ACCURACY_DOUBLE);
  circle.move({x, y});
  BOOST_CHECK_CLOSE(circle.getPosition().x, x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle.getPosition().y, y, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_scale_circle_area)
{
  shabinsky::Circle circle(13.0, {75.0, 76.0});
  const double area_circle = circle.getArea(),
    scale = 5.0;
  circle.scale(scale);
  BOOST_CHECK_CLOSE(area_circle * scale * scale, circle.getArea(), ACCURACY_DOUBLE);
}