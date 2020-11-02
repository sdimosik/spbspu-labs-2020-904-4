#define BOOST_TEST_MODULE MY_TEST

#include <cmath>

#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

BOOST_AUTO_TEST_SUITE(circle_test)

  const double EPSILON = 0.000001;
  const double RADIUS = 3.0;
  const double COEFFICIENT = 2.0;
  const unzhakov::point_t CENTER = {1.5, 2.6};
  const unzhakov::point_t MOVE_POINT = {4.3, 5.2};
  const double DX = 5.5;
  const double DY = 6.0;
  const double AREA = M_PI * RADIUS * RADIUS;

  BOOST_AUTO_TEST_CASE(circle_and_frame_data_after_moving_on_axes)
  {
    unzhakov::Circle circle(RADIUS, CENTER);
    const double frameHeight = circle.getFrameRect().height;
    const double frameWidth = circle.getFrameRect().width;
    circle.move(DX, DY);
    BOOST_CHECK_CLOSE(circle.getArea(), AREA, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, frameHeight, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, frameWidth, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(circle_and_frame_data_after_moving_in_point)
  {
    unzhakov::Circle circle(RADIUS, CENTER);
    const double frameHeight = circle.getFrameRect().height;
    const double frameWidth = circle.getFrameRect().width;
    circle.move(MOVE_POINT);
    BOOST_CHECK_CLOSE(circle.getArea(), AREA, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, frameHeight, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, frameWidth, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(circle_and_frame_data_after_scaling)
  {
    unzhakov::Circle circle(RADIUS, CENTER);
    circle.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(circle.getArea(), AREA * COEFFICIENT * COEFFICIENT, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(circle_invalid_radius)
  {
    BOOST_CHECK_THROW(unzhakov::Circle circle(0.0, CENTER), std::invalid_argument);
    BOOST_CHECK_THROW(unzhakov::Circle circle(-RADIUS, CENTER), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(circle_invalid_scale_coefficient)
  {
    unzhakov::Circle circle(RADIUS, CENTER);
    BOOST_CHECK_THROW(circle.scale(0.0), std::invalid_argument);
    BOOST_CHECK_THROW(circle.scale(-COEFFICIENT), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(rectangle_test)

  const double EPSILON = 0.000001;
  const double WIDTH = 10.0;
  const double HEIGHT = 15.0;
  const double COEFFICIENT = 2.0;
  const unzhakov::point_t CENTER = {1.5, 2.6};
  const unzhakov::point_t MOVE_POINT = {4.3, 5.2};
  const double DX = 5.5;
  const double DY = 6.0;
  const double AREA = WIDTH * HEIGHT;

  BOOST_AUTO_TEST_CASE(rectangle_and_frame_data_after_moving_on_axes)
  {
    unzhakov::Rectangle rectangle(WIDTH, HEIGHT, CENTER);
    const double frameWidth = rectangle.getFrameRect().width;
    const double frameHeight = rectangle.getFrameRect().height;
    rectangle.move(DX, DY);
    BOOST_CHECK_CLOSE(rectangle.getArea(), AREA, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, frameWidth, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, frameHeight, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectangle_and_frame_data_after_moving_in_point)
  {
    unzhakov::Rectangle rectangle(WIDTH, HEIGHT, CENTER);
    const double frameWidth = rectangle.getFrameRect().width;
    const double frameHeight = rectangle.getFrameRect().height;
    rectangle.move(MOVE_POINT);
    BOOST_CHECK_CLOSE(rectangle.getArea(), AREA, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, frameWidth, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, frameHeight, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectangle_and_frame_data_after_scaling)
  {
    unzhakov::Rectangle rectangle(WIDTH, HEIGHT, CENTER);
    rectangle.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(rectangle.getArea(), AREA * COEFFICIENT * COEFFICIENT, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectangle_invalid_scale_coefficient)
  {
    unzhakov::Rectangle rectangle(WIDTH, HEIGHT, CENTER);
    BOOST_CHECK_THROW(rectangle.scale(0.0), std::invalid_argument);
    BOOST_CHECK_THROW(rectangle.scale(-COEFFICIENT), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(rectangle_invalid_width)
  {
    BOOST_CHECK_THROW(unzhakov::Rectangle rectangle(0.0, HEIGHT, CENTER), std::invalid_argument);
    BOOST_CHECK_THROW(unzhakov::Rectangle rectangle(-WIDTH, HEIGHT, CENTER), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(rectangle_invalid_height)
  {
    BOOST_CHECK_THROW(unzhakov::Rectangle rectangle(WIDTH, 0.0, CENTER), std::invalid_argument);
    BOOST_CHECK_THROW(unzhakov::Rectangle rectangle(WIDTH, -HEIGHT, CENTER), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(triangle_test)

  const double EPSILON = 0.000001;
  const unzhakov::point_t VERTEX1 = {12, 11};
  const unzhakov::point_t VERTEX2 = {15, 15};
  const unzhakov::point_t VERTEX3 = {18, 11};
  const double COEFFICIENT = 2.0;
  const unzhakov::point_t MOVE_POINT = {4.3, 5.2};
  const double DX = 5.5;
  const double DY = 6.0;
  //const double AREA = 12;

  BOOST_AUTO_TEST_CASE(triangle_and_frame_data_after_moving_on_axes)
  {
    unzhakov::Triangle triangle(VERTEX1, VERTEX2, VERTEX3);
    const double frameWidth = triangle.getFrameRect().width;
    const double frameHeight = triangle.getFrameRect().height;
    const double area = triangle.getArea();
    triangle.move(DX, DY);
    BOOST_CHECK_CLOSE(triangle.getArea(), area, EPSILON);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, frameWidth, EPSILON);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, frameHeight, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectangle_and_frame_data_after_moving_in_point)
  {
    unzhakov::Triangle triangle(VERTEX1, VERTEX2, VERTEX3);
    const double frameWidth = triangle.getFrameRect().width;
    const double frameHeight = triangle.getFrameRect().height;
    const double area = triangle.getArea();
    triangle.move(MOVE_POINT);
    BOOST_CHECK_CLOSE(triangle.getArea(), area, EPSILON);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, frameWidth, EPSILON);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, frameHeight, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectangle_and_frame_data_after_scaling)
  {
    unzhakov::Triangle triangle(VERTEX1, VERTEX2, VERTEX3);
    const double area = triangle.getArea();
    triangle.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(triangle.getArea(), area * COEFFICIENT * COEFFICIENT, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(triangle_invalid_scale_coefficient)
  {
    unzhakov::Triangle triangle(VERTEX1, VERTEX2, VERTEX3);
    BOOST_CHECK_THROW(triangle.scale(0.0), std::invalid_argument);
    BOOST_CHECK_THROW(triangle.scale(-COEFFICIENT), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
