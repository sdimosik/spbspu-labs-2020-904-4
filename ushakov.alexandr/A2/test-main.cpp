#define BOOST_TEST_MODULE A1_TEST

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

const double ACCURACY = 0.00001;

BOOST_AUTO_TEST_CASE(test_invalid_argument_circle)
{
  BOOST_CHECK_THROW(ushakov::Circle circle({0.0, 0.0}, -1.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_width_rectangle)
{
  BOOST_CHECK_THROW(ushakov::Rectangle rectangle(-1.0, 2.0, {0.0, 0.0}), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_height_rectangle)
{
  BOOST_CHECK_THROW(ushakov::Rectangle rectangle(1.0, -2.0, {0.0, 0.0}), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_triangle)
{
  BOOST_CHECK_THROW(ushakov::Triangle triangle({1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_scale_circle)
{
  ushakov::Circle circle({0.0, 0.0}, 1);

  BOOST_CHECK_THROW(circle.scale(-2.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_scale_rectangle)
{
  ushakov::Rectangle rectangle(1.0, 3.0, {0.0, 0.0});

  BOOST_CHECK_THROW(rectangle.scale(-2.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_scale_triangle)
{
  ushakov::Triangle triangle({0.0, 0.0}, {0.0, 3.0}, {4.0, 0.0});

  BOOST_CHECK_THROW(triangle.scale(-2.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_scale_area_circle)
{
  ushakov::Circle circle({0.0, 0.0}, 1.0);

  const double CIRCLE_AREA = circle.getArea();
  const double COEFFICIENT = 2.0;

  circle.scale(COEFFICIENT);

  BOOST_CHECK_CLOSE(CIRCLE_AREA * COEFFICIENT * COEFFICIENT, circle.getArea(), ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_scale_area_rectangle)
{
  ushakov::Rectangle rectangle(1.0, 3.0, {0.0, 0.0});

  const double RECTANGLE_AREA = rectangle.getArea();
  const double COEFFICIENT = 2.0;

  rectangle.scale(COEFFICIENT);

  BOOST_CHECK_CLOSE(RECTANGLE_AREA * COEFFICIENT * COEFFICIENT, rectangle.getArea(), ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_scale_area_triangle)
{
  ushakov::Triangle triangle({0.0, 0.0}, {0.0, 3.0}, {4.0, 0.0});

  const double TRIANGLE_AREA = triangle.getArea();
  const double COEFFICIENT = 2.0;

  triangle.scale(COEFFICIENT);

  BOOST_CHECK_CLOSE(TRIANGLE_AREA * COEFFICIENT * COEFFICIENT, triangle.getArea(), ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_move_constancy_circle)
{
  ushakov::Circle circle({0.0, 0.0}, 1.0);
  ushakov::rectangle_t circleFrame = circle.getFrameRect();

  const double CIRCLE_AREA = circle.getArea();

  circle.move(2.0, -3.0);

  BOOST_CHECK_CLOSE(circleFrame.width, circle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(circleFrame.height, circle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(CIRCLE_AREA, circle.getArea(), ACCURACY);

  circle.move({1.0, 1.0});

  BOOST_CHECK_CLOSE(circleFrame.width, circle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(circleFrame.height, circle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(CIRCLE_AREA, circle.getArea(), ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_move_constancy_rectangle)
{
  ushakov::Rectangle rectangle(2.0, 5.0, {0.0, 0.0});
  ushakov::rectangle_t rectangleFrame = rectangle.getFrameRect();

  const double rectangleArea = rectangle.getArea();

  rectangle.move(2.0, -3.0);

  BOOST_CHECK_CLOSE(rectangleFrame.width, rectangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(rectangleFrame.height, rectangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(rectangleArea, rectangle.getArea(), ACCURACY);

  rectangle.move({1.0, 1.0});

  BOOST_CHECK_CLOSE(rectangleFrame.width, rectangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(rectangleFrame.height, rectangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(rectangleArea, rectangle.getArea(), ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_move_constancy_triangle)
{
  ushakov::Triangle triangle({0.0, 0.0}, {0.0, 3.0}, {4.0, 0.0});
  ushakov::rectangle_t triangleFrame = triangle.getFrameRect();

  const double TRIANGLE_AREA = triangle.getArea();

  triangle.move(2.0, -3.0);

  BOOST_CHECK_CLOSE(triangleFrame.width, triangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(triangleFrame.height, triangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(TRIANGLE_AREA, triangle.getArea(), ACCURACY);

  triangle.move({1.0, 1.0});

  BOOST_CHECK_CLOSE(triangleFrame.width, triangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(triangleFrame.height, triangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(TRIANGLE_AREA, triangle.getArea(), ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_correct_move_circle)
{
  ushakov::Circle circle({0.0, 0.0}, 1.0);

  const double DIFF_X = 3.0;
  const double DIFF_Y = 4.0;
  const double X = circle.getPosition().x;
  const double Y = circle.getPosition().y;

  circle.move(DIFF_X, DIFF_Y);

  BOOST_CHECK_CLOSE(circle.getPosition().x, DIFF_X + X, ACCURACY);
  BOOST_CHECK_CLOSE(circle.getPosition().y, DIFF_Y + Y, ACCURACY);

  circle.move({DIFF_X, DIFF_Y});

  BOOST_CHECK_CLOSE(circle.getPosition().x, DIFF_X, ACCURACY);
  BOOST_CHECK_CLOSE(circle.getPosition().y, DIFF_Y, ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_correct_move_rectangle)
{
  ushakov::Rectangle rectangle(1.0, 3.0, {0.0, 0.0});

  const double DIFF_X = 3.0;
  const double DIFF_Y = 4.0;
  const double X = rectangle.getPosition().x;
  const double Y = rectangle.getPosition().y;

  rectangle.move(DIFF_X, DIFF_Y);

  BOOST_CHECK_CLOSE(rectangle.getPosition().x, DIFF_X + X, ACCURACY);
  BOOST_CHECK_CLOSE(rectangle.getPosition().y, DIFF_Y + Y, ACCURACY);

  rectangle.move({DIFF_X, DIFF_Y});

  BOOST_CHECK_CLOSE(rectangle.getPosition().x, DIFF_X, ACCURACY);
  BOOST_CHECK_CLOSE(rectangle.getPosition().y, DIFF_Y, ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_correct_move_triangle)
{
  ushakov::Triangle triangle({0.0, 0.0}, {0.0, 3.0}, {4.0, 0.0});

  const double DIFF_X = 3.0;
  const double DIFF_Y = 4.0;
  const double X = triangle.getPosition().x;
  const double Y = triangle.getPosition().y;

  triangle.move(DIFF_X, DIFF_Y);

  BOOST_CHECK_CLOSE(triangle.getPosition().x, DIFF_X + X, ACCURACY);
  BOOST_CHECK_CLOSE(triangle.getPosition().y, DIFF_Y + Y, ACCURACY);

  triangle.move({DIFF_X, DIFF_Y});

  BOOST_CHECK_CLOSE(triangle.getPosition().x, DIFF_X, ACCURACY);
  BOOST_CHECK_CLOSE(triangle.getPosition().y, DIFF_Y, ACCURACY);
}
