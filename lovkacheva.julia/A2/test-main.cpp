#define BOOST_TEST_MODULE A2 Test

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "rectangle.hpp"
#include "circle.hpp"

const double TOLERANCE = 0.000001;

BOOST_AUTO_TEST_CASE(test_rectangle_constructor_invalid_width)
{
  BOOST_CHECK_THROW(lovkacheva::Rectangle rectangle({-10.0, 34.0, {4.56, 5.6}}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_rectangle_constructor_invalid_height)
{
  BOOST_CHECK_THROW(lovkacheva::Rectangle rectangle({10.0, -34.0, {4.56, 5.6}}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_circle_constructor_invalid_radius)
{
  BOOST_CHECK_THROW(lovkacheva::Circle circle(-23.6, {12.5, 0.1}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_rectangle_scale_invalid_coefficient)
{
  lovkacheva::Rectangle rectangle({10.0, 34.0, {4.56, 5.6}});
  BOOST_CHECK_THROW(rectangle.scale(-3.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_circle_scale_invalid_coefficient)
{
  lovkacheva::Circle circle(23.6, {12.5, 0.1});
  BOOST_CHECK_THROW(circle.scale(-3.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_rectangle_scale)
{
  const double coefficients[] = {2.5, 0.23};
  lovkacheva::Rectangle rectangle({3.45, 9.9032, {-0.8, 0.1}});
  for (double coefficient: coefficients)
  {
    const double area = rectangle.getArea();
    rectangle.scale(coefficient);
    BOOST_CHECK_CLOSE(area * coefficient * coefficient, rectangle.getArea(), TOLERANCE);
  }
}

BOOST_AUTO_TEST_CASE(test_circle_scale)
{
  const double coefficients[] = {2.5, 0.23};
  lovkacheva::Circle circle(8.5, {20.9, -0.6});
  for (double coefficient: coefficients)
  {
    const double area = circle.getArea();
    circle.scale(coefficient);
    BOOST_CHECK_CLOSE(area * coefficient * coefficient, circle.getArea(), TOLERANCE);
  }
}

BOOST_AUTO_TEST_CASE(test_rectangle_move)
{
  lovkacheva::Rectangle rectangle({3.45, 9.9032, {-0.8, 0.1}});
  const lovkacheva::rectangle_t formerFrameRectangle = rectangle.getFrameRect();
  const double dx = 1.0;
  const double dy = 2.0;
  rectangle.move(dx, dy);
  BOOST_CHECK_CLOSE(formerFrameRectangle.pos.x + dx, rectangle.getFrameRect().pos.x, TOLERANCE);
  BOOST_CHECK_CLOSE(formerFrameRectangle.pos.y + dy, rectangle.getFrameRect().pos.y, TOLERANCE);
  const lovkacheva::point_t newPosition = {-1.8, 2.78};
  rectangle.move(newPosition);
  BOOST_CHECK_CLOSE(newPosition.x, rectangle.getFrameRect().pos.x, TOLERANCE);
  BOOST_CHECK_CLOSE(newPosition.y, rectangle.getFrameRect().pos.y, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(test_circle_move)
{
  lovkacheva::Circle circle(8.5, {20.9, -0.6});
  const lovkacheva::rectangle_t formerFrameRectangle = circle.getFrameRect();
  const double dx = 1.0;
  const double dy = 2.0;
  circle.move(dx, dy);
  BOOST_CHECK_CLOSE(formerFrameRectangle.pos.x + dx, circle.getFrameRect().pos.x, TOLERANCE);
  BOOST_CHECK_CLOSE(formerFrameRectangle.pos.y + dy, circle.getFrameRect().pos.y, TOLERANCE);
  const lovkacheva::point_t newPosition = {-1.8, 2.78};
  circle.move(newPosition);
  BOOST_CHECK_CLOSE(newPosition.x, circle.getFrameRect().pos.x, TOLERANCE);
  BOOST_CHECK_CLOSE(newPosition.y, circle.getFrameRect().pos.y, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(test_rectangle_properties_unchanged_after_movement)
{
  lovkacheva::Rectangle rectangle({3.45, 9.9032, {-0.8, 0.1}});
  const lovkacheva::rectangle_t formerFrameRectangle = rectangle.getFrameRect();
  const double area = rectangle.getArea();
  rectangle.move(1.0, 2.0);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, formerFrameRectangle.width, TOLERANCE);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, formerFrameRectangle.height, TOLERANCE);
  BOOST_CHECK_CLOSE(rectangle.getArea(), area, TOLERANCE);
  rectangle.move({-1.8, 2.78});
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, formerFrameRectangle.width, TOLERANCE);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, formerFrameRectangle.height, TOLERANCE);
  BOOST_CHECK_CLOSE(rectangle.getArea(), area, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(test_circle_properties_unchanged_after_movement)
{
  lovkacheva::Circle circle(8.5, {20.9, -0.6});
  const lovkacheva::rectangle_t formerFrameRectangle = circle.getFrameRect();
  const double area = circle.getArea();
  circle.move(1.0, 2.0);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, formerFrameRectangle.width, TOLERANCE);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, formerFrameRectangle.height, TOLERANCE);
  BOOST_CHECK_CLOSE(circle.getArea(), area, TOLERANCE);
  circle.move({-1.8, 2.78});
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, formerFrameRectangle.width, TOLERANCE);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, formerFrameRectangle.height, TOLERANCE);
  BOOST_CHECK_CLOSE(circle.getArea(), area, TOLERANCE);
}
