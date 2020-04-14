#define BOOST_TEST_MODULE myTest

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "rectangle.hpp"
#include "circle.hpp"

const double TOLERANCE_RANGE = 0.00001;

BOOST_AUTO_TEST_CASE(test_invalid_radius_circle)
{
  BOOST_CHECK_THROW(bakaeva::Circle circle(-3.5, {0.4, 4.0}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_coefficient_scaling_circle)
{
  bakaeva::Circle circle(3.5, {0.4, 4.0});
  BOOST_CHECK_THROW(circle.scale(-3.2), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_width_rectangle)
{
  BOOST_CHECK_THROW(bakaeva::Rectangle rectangle(-2.5, 7.8, {-2.3, 6.0}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_height_rectangle)
{
  BOOST_CHECK_THROW(bakaeva::Rectangle rectangle(2.5, -7.8, {-2.3, 6.0}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_coefficient_scaling_rectangle)
{
  bakaeva::Rectangle rectangle(2.5, 7.8, {-2.3, 6.0});
  BOOST_CHECK_THROW(rectangle.scale(-4.25), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_immutability_circle_moving)
{
  bakaeva::Circle circle(1.5, {1.0, 4.5});
  bakaeva::rectangle_t frameRect = circle.getFrameRect();
  const double area = circle.getArea();

  circle.move({3.7, 10.0});
  BOOST_CHECK_CLOSE(frameRect.width, circle.getFrameRect().width, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.height, circle.getFrameRect().height, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(area, circle.getArea(), TOLERANCE_RANGE);
  
  circle.move(9.4, 2.6);
  BOOST_CHECK_CLOSE(frameRect.width, circle.getFrameRect().width, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.height, circle.getFrameRect().height, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(area, circle.getArea(), TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_immutability_rectangle_moving)
{
  bakaeva::Rectangle rectangle(6.4, 3.0, {3.8, 8.0});
  bakaeva::rectangle_t frameRect = rectangle.getFrameRect();
  const double area = rectangle.getArea();

  rectangle.move({3.8, 10.0});
  BOOST_CHECK_CLOSE(frameRect.width, rectangle.getFrameRect().width, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.height, rectangle.getFrameRect().height, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(area, rectangle.getArea(), TOLERANCE_RANGE);

  rectangle.move(5.0, 2.0);
  BOOST_CHECK_CLOSE(frameRect.width, rectangle.getFrameRect().width, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.height, rectangle.getFrameRect().height, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(area, rectangle.getArea(), TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_circle_scaling)
{
  bakaeva::Circle circle(5.5, {4.6, -5.0});
  const double area = circle.getArea();
  const double coefficient = 1.5;
  circle.scale(coefficient);
  BOOST_CHECK_CLOSE(area * coefficient * coefficient, circle.getArea(), TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_rectangle_scaling)
{
  bakaeva::Rectangle rectangle(7.9, 6.0, {-2.0, 4.3});
  const double area = rectangle.getArea();
  const double coefficient = 2.5;
  rectangle.scale(coefficient);
  BOOST_CHECK_CLOSE(area * coefficient * coefficient, rectangle.getArea(), TOLERANCE_RANGE);
}
