#define BOOST_TEST_MODULE MYTEST

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

const double TOLERANCE_RANGE = 0.00001;

BOOST_AUTO_TEST_CASE(test_invalid_radius_circle)
{
  BOOST_CHECK_THROW(vasilevskaya::Circle circle({ 0.0, 0.0 }, -1.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_coefficient_scaling_circle)
{
  vasilevskaya::Circle circle({ 0.0, 0.0 }, 1.0);
  BOOST_CHECK_THROW(circle.scale(-2.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_width_rectangle)
{
  BOOST_CHECK_THROW(vasilevskaya::Rectangle myRectangle(-2.5, 7.8, { -2.3, 6.0 }), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_height_rectangle)
{
  BOOST_CHECK_THROW(vasilevskaya::Rectangle myRectangle(2.5, -7.8, { -2.3, 6.0 }), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_coefficient_scaling_rectangle)
{
  vasilevskaya::Rectangle myRectangle(2.5, 7.8, { -2.3, 6.0 });
  BOOST_CHECK_THROW(myRectangle.scale(-4.25), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_triangle)
{
  BOOST_CHECK_THROW(vasilevskaya::Triangle myTriangle({ 1.0, 1.0 }, { 2.0, 2.0 }, { 3.0, 3.0 }), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_scale_triangle)
{
  vasilevskaya::Triangle myTriangle({ 0.0, 1.0 }, { 3.0, 1.0 }, { 4.0, 0.0 });
  BOOST_CHECK_THROW(myTriangle.scale(-2.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_immutability_circle_moving)
{
  vasilevskaya::Circle myCircle({ 5, 4 }, 1.5);
  vasilevskaya::rectangle_t frameRect = myCircle.getFrameRect();
  const double area = myCircle.getArea();

  myCircle.move({ 3.7, 10.0 });
  BOOST_CHECK_CLOSE(frameRect.width, myCircle.getFrameRect().width, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.height, myCircle.getFrameRect().height, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(area, myCircle.getArea(), TOLERANCE_RANGE);

  myCircle.move(9.4, 2.6);
  BOOST_CHECK_CLOSE(frameRect.width, myCircle.getFrameRect().width, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.height, myCircle.getFrameRect().height, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(area, myCircle.getArea(), TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_immutability_rectangle_moving)
{
  vasilevskaya::Rectangle myRectangle(6.4, 3.0, { 3.8, 8.0 });
  vasilevskaya::rectangle_t frameRect = myRectangle.getFrameRect();
  const double area = myRectangle.getArea();

  myRectangle.move({ 3.8, 10.0 });
  BOOST_CHECK_CLOSE(frameRect.width, myRectangle.getFrameRect().width, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.height, myRectangle.getFrameRect().height, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(area, myRectangle.getArea(), TOLERANCE_RANGE);

  myRectangle.move(5.0, 2.0);
  BOOST_CHECK_CLOSE(frameRect.width, myRectangle.getFrameRect().width, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.height, myRectangle.getFrameRect().height, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(area, myRectangle.getArea(), TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_immutability_triangle_moving)
{
  vasilevskaya::Triangle myTriangle({ 0.0, 0.0 }, { 0.0, 3.0 }, { 4.0, 0.0 });
  vasilevskaya::rectangle_t frameRect = myTriangle.getFrameRect();
  const double area = myTriangle.getArea();

  myTriangle.move({ 1.0, 1.0 });
  BOOST_CHECK_CLOSE(frameRect.width, myTriangle.getFrameRect().width, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.height, myTriangle.getFrameRect().height, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(area, myTriangle.getArea(), TOLERANCE_RANGE);

  myTriangle.move(2.0, -3.0);
  BOOST_CHECK_CLOSE(frameRect.width, myTriangle.getFrameRect().width, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.height, myTriangle.getFrameRect().height, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(area, myTriangle.getArea(), TOLERANCE_RANGE);
}


BOOST_AUTO_TEST_CASE(test_circle_scaling)
{
  vasilevskaya::Circle myCircle({ 4.6, -5.0 }, 5.5);
  const double area = myCircle.getArea();
  const double coefficient = 2.0;
  myCircle.scale(coefficient);
  BOOST_CHECK_CLOSE(area * coefficient * coefficient, myCircle.getArea(), TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_rectangle_scaling)
{
  vasilevskaya::Rectangle myRectangle(7.9, 6.0, { -2.0, 4.3 });
  const double area = myRectangle.getArea();
  const double coefficient = 2.0;
  myRectangle.scale(coefficient);
  BOOST_CHECK_CLOSE(area * coefficient * coefficient, myRectangle.getArea(), TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_triangle_scaling)
{
  vasilevskaya::Triangle myTriangle({ 0.0, 0.0 }, { 0.0, 3.0 }, { 4.0, 0.0 });
  const double area = myTriangle.getArea();
  const double coefficient = 2.0;
  myTriangle.scale(coefficient);
  BOOST_CHECK_CLOSE(area * coefficient * coefficient, myTriangle.getArea(), TOLERANCE_RANGE);
}
