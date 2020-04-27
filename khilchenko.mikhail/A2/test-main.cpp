#define BOOST_TEST_MODULE test

#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"

const double ACCURACY = 0.000001;

BOOST_AUTO_TEST_CASE(test_invalid_argument_circle)
{
  khilchenko::point_t pos { 1, 1 };
  BOOST_CHECK_THROW(khilchenko::Circle circle( -5, pos), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_rectangle)
{
  khilchenko::point_t pos { 1, 1 };
  BOOST_CHECK_THROW(khilchenko::Rectangle rectangle( -5, -5, pos ) , std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_scale_circle)
{
  khilchenko::point_t pos{ 1, 1 };
  khilchenko::Circle circle(5,  pos);
  BOOST_CHECK_THROW(circle.scale(-2), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_scale_rectangle)
{
  khilchenko::point_t pos { 1, 1 };
  khilchenko::Rectangle rectangle(3, 7, pos);
  BOOST_CHECK_THROW( rectangle.scale(-2), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_correct_move_circle)
{
  khilchenko::point_t pos1{ 1, 1 };
  khilchenko::Circle circle1(5, pos1);
  circle1.move(5, 5);
  BOOST_CHECK_CLOSE((circle1.getCenter().x - 5), pos1.x, ACCURACY);
  BOOST_CHECK_CLOSE((circle1.getCenter().y - 5), pos1.y, ACCURACY);
  khilchenko::point_t pos2{ 0, 0 };
  khilchenko::Circle circle2(6, pos2);
  khilchenko::point_t newPos{ 25, 50 };
  circle2.move(newPos);
  BOOST_CHECK_CLOSE((circle2.getCenter().x - 25), pos2.x, ACCURACY);
  BOOST_CHECK_CLOSE((circle2.getCenter().y - 50), pos2.y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_correct_move_rectangle)
{
  khilchenko::point_t pos1{ 1, 1 };
  khilchenko::Rectangle rectangle1(5, 5, pos1);
  rectangle1.move(5, 5);
  BOOST_CHECK_CLOSE((rectangle1.getCenter().x - 5), pos1.x, ACCURACY);
  BOOST_CHECK_CLOSE((rectangle1.getCenter().y - 5), pos1.y, ACCURACY);
  khilchenko::point_t pos2{ 0, 0 };
  khilchenko::Rectangle rectangle2(6, 5, pos2);
  khilchenko::point_t newPos{ 25, 50 };
  rectangle2.move(newPos);
  BOOST_CHECK_CLOSE((rectangle2.getCenter().x - 25), pos2.x, ACCURACY);
  BOOST_CHECK_CLOSE((rectangle2.getCenter().y - 50), pos2.y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_immutability_move_circle)
{
  khilchenko::point_t pos1{ 1, 1 };
  double startRad1 = 5;
  khilchenko::Circle circle1( startRad1, pos1) ;
  double startArea1 = circle1.getArea();
  circle1.move(5, 5);
  BOOST_CHECK_CLOSE(circle1.getFrameRect().width, 2 * startRad1, ACCURACY);
  BOOST_CHECK_CLOSE(startArea1, circle1.getArea(), ACCURACY);
  khilchenko::point_t pos2{ 0, 0 };
  double startRad2 = 10;
  khilchenko::Circle circle2(startRad2, pos2);
  double startArea2 = circle2.getArea();
  khilchenko::point_t newPos{ 25, 50 };
  circle2.move(newPos);
  BOOST_CHECK_CLOSE(circle2.getFrameRect().width, 2 * startRad2, ACCURACY);
  BOOST_CHECK_CLOSE(startArea2, circle2.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_immutability_move_rectangle)
{
  khilchenko::point_t pos1{ 1, 1 };
  double startWidth = 5;
  double startHeight = 10;
  khilchenko::Rectangle rectangle1(startWidth, startHeight, pos1) ;
  double startArea1 = rectangle1.getArea();
  rectangle1.move(5, 5);
  BOOST_CHECK_CLOSE(rectangle1.getFrameRect().width, startWidth, ACCURACY);
  BOOST_CHECK_CLOSE(rectangle1.getFrameRect().height, startHeight, ACCURACY);
  BOOST_CHECK_CLOSE(startArea1, rectangle1.getArea(), ACCURACY);
  khilchenko::point_t pos2{ 0, 0 };
  khilchenko::Rectangle rectangle2(startWidth, startHeight, pos2);
  double startArea2 = rectangle2.getArea();
  khilchenko::point_t newPos{ 25, 50 };
  rectangle2.move(newPos);
  BOOST_CHECK_CLOSE(rectangle2.getFrameRect().width, startWidth, ACCURACY);
  BOOST_CHECK_CLOSE(rectangle2.getFrameRect().height, startHeight, ACCURACY);
  BOOST_CHECK_CLOSE(startArea2, rectangle2.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_quadratic_scale_circle)
{
  khilchenko::point_t pos{ 1, 1 };
  double startRad = 5;
  khilchenko::Circle circle( startRad, pos) ;
  double startArea = circle.getArea();
  circle.scale(2);
  BOOST_CHECK_CLOSE((startArea * 4), circle.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_quadratic_scale_rectangle)
{
  khilchenko::point_t pos{ 1, 1 };
  double startWidth = 5;
  double startHeight = 10;
  khilchenko::Rectangle rectangle(startWidth, startHeight, pos) ;
  double startArea = rectangle.getArea();
  rectangle.scale(2);
  BOOST_CHECK_CLOSE(startArea * 4, rectangle.getArea(), ACCURACY);
}
