#define BOOST_TEST_MODULE maintest

#include <cmath>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "rectangle.hpp"
#include "circle.hpp"

const double ACCURACY_DOUBLE = 0.0001;

BOOST_AUTO_TEST_CASE(test_invalid_argument_rectangle)
{
  BOOST_CHECK_THROW(meynik::Rectangle rect({-2.0, 2.0}, -4.0, 9.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_rectangle_scale)
{
  meynik::Rectangle rect({-2.0, 2.0}, 4.0, 9.0);
  BOOST_CHECK_THROW(rect.scale(-2.5), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_circle)
{
  BOOST_CHECK_THROW(meynik::Circle circle(-2.28, {1.2, 2.1}), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_circle_scale)
{
  meynik::Circle circle(-2.28, {1.2, 2.1});
  BOOST_CHECK_THROW(circle.scale(-2.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_correct_move_rectangle)
{
  meynik::Rectangle rect({-2.0, 2.0}, 10.0, 10.0);
  const double deltaX = 6,
    deltaY = 6,
    primaryX = rect.getPosition().x,
    primaryY = rect.getPosition().y;
  rect.move(deltaX, deltaY);
  BOOST_CHECK_CLOSE(rect.getPosition().x, deltaX + primaryX, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rect.getPosition().y, deltaY + primaryY, ACCURACY_DOUBLE);
  rect.move({deltaX, deltaY});
  BOOST_CHECK_CLOSE(rect.getPosition().x, deltaX, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rect.getPosition().y, deltaY, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_correct_move_circle)
{
  meynik::Circle circle(2.28, {1.2, 2.1});
  const double deltaX = 2.1,
    deltaY = 1.2,
    primaryX = circle.getCentre().x,
    primaryY= circle.getCentre().y;
  circle.move(deltaX, deltaY);
  BOOST_CHECK_CLOSE(circle.getCentre().x, deltaX + primaryX, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle.getCentre().y, deltaY + primaryY, ACCURACY_DOUBLE);
  circle.move({deltaX, deltaY});
  BOOST_CHECK_CLOSE(circle.getCentre().x, deltaX, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle.getCentre().y, deltaY, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_scale_rectangle_area)
{
  meynik::Rectangle rect({1.2, 2.1}, 2.0, 6.0);
  const double rect_area = rect.getArea(),
    scale = 2.5;
  rect.scale(scale);
  BOOST_CHECK_CLOSE(rect_area * scale * scale, rect.getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_scale_circle_area)
{
  meynik::Circle circle(10.0, {1.2, 2.1});
  const double circle_area = circle.getArea(),
    scale = 0.1;
  circle.scale(scale);
  BOOST_CHECK_CLOSE(circle_area * scale * scale, circle.getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_permanency_move_rectange)
{
  meynik::Rectangle rect({-2.0, 2.0}, 10.0, 10.0);
  const meynik::rectangle_t frameRect = rect.getFrameRect();
  const double rect_area = rect.getArea();
  rect.move({2.0, -2.0});
  BOOST_CHECK_CLOSE(frameRect.height, rect.getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.width, rect.getFrameRect().width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rect_area, rect.getArea(), ACCURACY_DOUBLE);
  rect.move(-25.0, 25.0);
  BOOST_CHECK_CLOSE(frameRect.height, rect.getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.width, rect.getFrameRect().width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rect_area, rect.getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_permanency_move_circle)
{
  meynik::Circle circle(2.28, {1.2, 2.1});
  const meynik::rectangle_t frameRect = circle.getFrameRect();
  const double circle_area = circle.getArea();
  circle.move(2.1, 1.2);
  BOOST_CHECK_CLOSE(frameRect.height, circle.getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.width, circle.getFrameRect().width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle_area, circle.getArea(), ACCURACY_DOUBLE);
  circle.move({-3.3, -3.3});
  BOOST_CHECK_CLOSE(frameRect.height, circle.getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.width, circle.getFrameRect().width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle_area, circle.getArea(), ACCURACY_DOUBLE);
}
