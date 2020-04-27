#define BOOST_TEST_MODULE test

#include <cmath>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"

const double ACCURACY = 0.00001;

BOOST_AUTO_TEST_CASE(test_invalid_argument_circle)
{
  BOOST_CHECK_THROW(meshcheryakov::Circle circle( -5.0, {1.0, 1.0}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_scale_circle)
{
  meshcheryakov::Circle circle (5.0, {1.0, 1.0});
  BOOST_CHECK_THROW(circle.scale(-2.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invariability_move_circle)
{
  meshcheryakov::Circle circle (5.0, {1.0, 1.0});
  meshcheryakov::rectangle_t frame_cir = circle.getFrameRect();
  double area_cir = circle.getArea();
  circle.move(10.0, 10.0);
  BOOST_CHECK_CLOSE(frame_cir.width, circle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(frame_cir.height, circle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(circle.getArea(), area_cir, ACCURACY);
  meshcheryakov::point_t point_cir {5.0, 5.0};
  circle.move(point_cir);
  BOOST_CHECK_CLOSE(frame_cir.width, circle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(frame_cir.height, circle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(circle.getArea(), area_cir, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_correct_move_circle)
{
  meshcheryakov::point_t dot1 {1.0, 1.0};
  meshcheryakov::Circle circle (10.0, dot1);
  circle.move(2.0, 2.0);
  BOOST_CHECK_CLOSE(circle.getPosition().x - 2.0, dot1.x, ACCURACY);
  BOOST_CHECK_CLOSE(circle.getPosition().y - 2.0, dot1.y, ACCURACY);
  meshcheryakov::point_t dot2 {3.0, 3.0};
  circle.move(dot2);
  BOOST_CHECK_CLOSE(circle.getPosition().x, dot2.x, ACCURACY);
  BOOST_CHECK_CLOSE(circle.getPosition().y, dot2.y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_scale_circle)
{
  meshcheryakov::Circle circle (5.0, {1.0, 1.0});
  double area_cir = circle.getArea();
  circle.scale(5.0);
  BOOST_CHECK_CLOSE(circle.getArea(), area_cir * 5.0 * 5.0, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_rectangle)
{
  BOOST_CHECK_THROW(meshcheryakov::Rectangle rectangle ({-5, -5, {1.0, 1.0}}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_scale_rectangle)
{
  meshcheryakov::Rectangle rectangle ({5.0, 5.0, {1.0, 1.0}});
  BOOST_CHECK_THROW(rectangle.scale(-3.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invariability_move_rectangle)
{
  meshcheryakov::Rectangle rectangle ({5.0, 5.0, {1.0, 1.0}});
  meshcheryakov::rectangle_t frame_rect = rectangle.getFrameRect();
  double area_rect = rectangle.getArea();
  rectangle.move(10.0, 10.0);
  BOOST_CHECK_CLOSE(frame_rect.width, rectangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(frame_rect.height, rectangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(rectangle.getArea(), area_rect, ACCURACY);
  meshcheryakov::point_t point_rect {5.0, 5.0};
  rectangle.move(point_rect);
  BOOST_CHECK_CLOSE(frame_rect.width, rectangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(frame_rect.height, rectangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(rectangle.getArea(), area_rect, ACCURACY);
}


BOOST_AUTO_TEST_CASE(test_correct_move_rectangle)
{
  meshcheryakov::point_t dot1 {1.0, 1.0};
  meshcheryakov::Rectangle rectangle ({10.0, 10.0, dot1});
  rectangle.move(2.0, 2.0);
  BOOST_CHECK_CLOSE(rectangle.getPosition().x - 2.0, dot1.x, ACCURACY);
  BOOST_CHECK_CLOSE(rectangle.getPosition().y - 2.0, dot1.y, ACCURACY);
  meshcheryakov::point_t dot2 {3.0, 3.0};
  rectangle.move(dot2);
  BOOST_CHECK_CLOSE(rectangle.getPosition().x, dot2.x, ACCURACY);
  BOOST_CHECK_CLOSE(rectangle.getPosition().y, dot2.y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_scale_rectangle)
{
  meshcheryakov::Rectangle rectangle ({5.0, 5.0, {1.0, 1.0}});
  double area_rect = rectangle.getArea();
  rectangle.scale(5.0);
  BOOST_CHECK_CLOSE(rectangle.getArea(), area_rect * 5.0 * 5.0, ACCURACY);
}
