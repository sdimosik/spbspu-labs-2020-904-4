#define BOOST_TEST_MODULE mytest
#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "rectangle.hpp"
#include "circle.hpp"

const double PERMISSIBLE_ACCURACY = 0.00001;

BOOST_AUTO_TEST_CASE(test_invalid_radius_circle)
{
  BOOST_CHECK_THROW(bulanov::Circle circle(-0.2, {1.1, 2.1}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_rate_scaling_circle)
{
  bulanov::Circle circle(5.11, {1.1, 2.1});
  BOOST_CHECK_THROW(circle.scale(-5.2), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_width_rectangle)
{
  BOOST_CHECK_THROW(bulanov::Rectangle rectangle({3.2, 2.1}, -3, 7), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_height_rectangle)
{
  BOOST_CHECK_THROW(bulanov::Rectangle rectangle({3.2, 2.1}, 3, 0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_rate_scaling_rectangle)
{
  bulanov::Rectangle rectangle({3.2, 2.1}, 3, 7);
  BOOST_CHECK_THROW(rectangle.scale(-1.7), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_permanency_circle_moving)
{
  bulanov::Circle circle(5.11, {1.1, 2.1});
  const bulanov::rectangle_t frameRect = circle.getFrameRect();
  const double area = circle.getArea();

  circle.move(11.2, 12.3);
  BOOST_CHECK_CLOSE(frameRect.width, circle.getFrameRect().width, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.height, circle.getFrameRect().height, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(area, circle.getArea(), PERMISSIBLE_ACCURACY);

  circle.move({-10.2, -9.3});
  BOOST_CHECK_CLOSE(frameRect.width, circle.getFrameRect().width, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.height, circle.getFrameRect().height, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(area, circle.getArea(), PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_circle_scaling_area)
{
  bulanov::Circle circle(5.11, {1.1, 2.1});
  const double area = circle.getArea();
  const double rate = 0.7;
  circle.scale(rate);
  BOOST_CHECK_CLOSE(area * rate * rate, circle.getArea(), PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_permanency_rectangle_moving)
{
  bulanov::Rectangle rectangle({3.2, 2.1}, 3, 7);
  bulanov::rectangle_t frameRect = rectangle.getFrameRect();
  const double area = rectangle.getArea();

  rectangle.move({2.2, 10.3});
  BOOST_CHECK_CLOSE(frameRect.width, rectangle.getFrameRect().width, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.height, rectangle.getFrameRect().height, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(area, rectangle.getArea(), PERMISSIBLE_ACCURACY);

  rectangle.move(-5.2, -3.3);
  BOOST_CHECK_CLOSE(frameRect.width, rectangle.getFrameRect().width, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.height, rectangle.getFrameRect().height, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(area, rectangle.getArea(), PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rectangle_scaling_area)
{
  bulanov::Rectangle rectangle({1.0, 1.0}, 10.0, 14.5);
  const double area = rectangle.getArea();
  const double rate = 3.1;
  rectangle.scale(rate);
  BOOST_CHECK_CLOSE(area * rate * rate, rectangle.getArea(), PERMISSIBLE_ACCURACY);
}







