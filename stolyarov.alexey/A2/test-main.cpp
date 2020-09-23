#define BOOST_TEST_MODULE mytests

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "../common/circle.hpp"
#include "../common/rectangle.hpp"

const double ACCURACY = 0.0000001;

BOOST_AUTO_TEST_CASE(test_rectangle_constructor_valid)
{
  double width = 1.7;
  double height = 14.3;
  stolyarov::point_t pos{ 12.1, 43.1 };
  stolyarov::Rectangle rectangle(width, height, pos);
  BOOST_CHECK_CLOSE(width, rectangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(height, rectangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(pos.x, rectangle.getFrameRect().pos.x, ACCURACY);
  BOOST_CHECK_CLOSE(pos.y, rectangle.getFrameRect().pos.y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rectangle_constructor_invalid_negative_width)
{
  BOOST_CHECK_THROW(stolyarov::Rectangle rectangle(-1, 2.1, stolyarov::point_t{ 5, 5 }), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_rectangle_constructor_invalid_zero_width)
{
  BOOST_CHECK_THROW(stolyarov::Rectangle rectangle(0, 2.1, stolyarov::point_t{ 5, 5 }), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_rectangle_constructor_invalid_negative_height)
{
  BOOST_CHECK_THROW(stolyarov::Rectangle rectangle(2.1, -1.2, stolyarov::point_t{ 5, 5 }), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_rectangle_constructor_invalid_zero_height)
{
  BOOST_CHECK_THROW(stolyarov::Rectangle rectangle(2.1, 0, stolyarov::point_t{ 5, 5 }), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_rectangle_move_by_invariability_width)
{
  stolyarov::Rectangle rectangle(5, 5, stolyarov::point_t{ 5,5 });
  const stolyarov::rectangle_t tempRect = rectangle.getFrameRect();
  rectangle.move(12.3, 3.4);
  BOOST_CHECK_CLOSE(tempRect.width, rectangle.getFrameRect().width, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rectangle_move_to_invariability_width)
{
  stolyarov::Rectangle rectangle(5, 5, stolyarov::point_t{ 5,5 });
  const stolyarov::rectangle_t tempRect = rectangle.getFrameRect();
  rectangle.move(stolyarov::point_t{12.3, 4.1});
  BOOST_CHECK_CLOSE(tempRect.width, rectangle.getFrameRect().width, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rectangle_move_by_invariability_height)
{
  stolyarov::Rectangle rectangle(5, 5, stolyarov::point_t{ 5,5 });
  const stolyarov::rectangle_t tempRect = rectangle.getFrameRect();
  rectangle.move(12.3, 3.4);
  BOOST_CHECK_CLOSE(tempRect.height, rectangle.getFrameRect().height, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rectangle_move_to_invariability_height)
{
  stolyarov::Rectangle rectangle(5, 5, stolyarov::point_t{ 5,5 });
  const stolyarov::rectangle_t tempRect = rectangle.getFrameRect();
  rectangle.move(stolyarov::point_t{ 5.1, 2.3 });
  BOOST_CHECK_CLOSE(tempRect.height, rectangle.getFrameRect().height, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rectangle_move_by_invariability_area)
{
  stolyarov::Rectangle rectangle(5, 5, stolyarov::point_t{ 1.2, 13.4 });
  const double area = rectangle.getArea();
  rectangle.move(12.3, 5.6);
  BOOST_CHECK_CLOSE(area, rectangle.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rectangle_move_to_invariability_area)
{
  stolyarov::Rectangle rectangle(5, 5, stolyarov::point_t{ 1.2, 13.4 });
  const double area = rectangle.getArea();
  rectangle.move(stolyarov::point_t{12.3, 23.1});
  BOOST_CHECK_CLOSE(area, rectangle.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rectangle_scale_quadratic_change_area)
{
  stolyarov::Rectangle rectangle(5, 5, stolyarov::point_t{ 1.2, 13.4 });
  const double area = rectangle.getArea();
  const double rate = 1.3;
  rectangle.scale(rate);
  BOOST_CHECK_CLOSE(area * rate * rate, rectangle.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rectangle_scale_invalide_negative_rate)
{
  stolyarov::Rectangle rectangle(12, 3, stolyarov::point_t{ 3.4, 12.4 });
  BOOST_CHECK_THROW(rectangle.scale(-12.3), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_rectangle_scale_invalide_zero_rate)
{
  stolyarov::Rectangle rectangle(12.3, 4.1, stolyarov::point_t{ 1.1, 3.1 });
  BOOST_CHECK_THROW(rectangle.scale(0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_circle_constructor_valid)
{
  double radius = 14.1;
  stolyarov::point_t pos{ 12.1, 15.6 };
  stolyarov::Circle circle(radius, pos);
  BOOST_CHECK_CLOSE(radius, circle.getFrameRect().height / 2, ACCURACY);
  BOOST_CHECK_CLOSE(pos.x, circle.getFrameRect().pos.x, ACCURACY);
  BOOST_CHECK_CLOSE(pos.y, circle.getFrameRect().pos.y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_circle_constructor_invalid_negative_radius)
{
  BOOST_CHECK_THROW(stolyarov::Circle circle(-1.2, stolyarov::point_t{ 5, 5 }), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_circle_constructor_invalid_zero_radius)
{
  BOOST_CHECK_THROW(stolyarov::Circle circle(0, stolyarov::point_t{ 5, 5 }), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_circle_move_by_invariability_radius)
{
  stolyarov::Circle circle(5, stolyarov::point_t{ 5,5 });
  const stolyarov::rectangle_t tempRect = circle.getFrameRect();
  circle.move(12.3, 3.4);
  BOOST_CHECK_CLOSE(tempRect.height / 2, circle.getFrameRect().height / 2, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_circle_move_to_invariability_radius)
{
  stolyarov::Circle circle(5, stolyarov::point_t{ 5,5 });
  const stolyarov::rectangle_t tempRect = circle.getFrameRect();
  circle.move(stolyarov::point_t{12.1, 4.1});
  BOOST_CHECK_CLOSE(tempRect.height / 2, circle.getFrameRect().height / 2, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_circle_move_by_invariability_area)
{
  stolyarov::Circle circle(12.1, stolyarov::point_t{ 4.1, 56.1 });
  const double area = circle.getArea();
  circle.move(14.1, 21.5);
  BOOST_CHECK_CLOSE(area, circle.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_circle_move_to_invariability_area)
{
  stolyarov::Circle circle(12.1, stolyarov::point_t{ 4.1, 56.1 });
  const double area = circle.getArea();
  circle.move(stolyarov::point_t{12.1, 45.1});
  BOOST_CHECK_CLOSE(area, circle.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_circle_scale_quadratic_change_area)
{
  stolyarov::Circle circle(14.1, stolyarov::point_t{ 54.1, 12.1 });
  const double area = circle.getArea();
  const double rate = 1.6;
  circle.scale(rate);
  BOOST_CHECK_CLOSE(area * rate * rate, circle.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_circle_scale_invalide_negative_rate)
{
  stolyarov::Circle circle(12.1, stolyarov::point_t{ 32.1, 54.1 });
  BOOST_CHECK_THROW(circle.scale(-12.1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_circle_scale_invalide_zero_rate)
{
  stolyarov::Circle circle(41.2, stolyarov::point_t{ 43.1, 65.1 });
  BOOST_CHECK_THROW(circle.scale(0), std::invalid_argument);
}
