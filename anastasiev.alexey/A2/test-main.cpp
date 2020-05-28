#define BOOST_TEST_MODULE mytests

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

const double ACCURACY = 0.00001;

BOOST_AUTO_TEST_CASE(test_invalid_argument_circle)
{
  BOOST_CHECK_THROW(anastasiev::Circle circle(-5.0, {0.0, 0.0}), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_rectangle)
{
  BOOST_CHECK_THROW(anastasiev::Rectangle rectangle(-5.0, 5.0, {0.0, 0.0}), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_triangle)
{
  BOOST_CHECK_THROW(anastasiev::Triangle triangle({1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_circle_scale)
{
  anastasiev::Circle circle(5.0, {0.0, 0.0});
  BOOST_CHECK_THROW(circle.scale(-2.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_rectangle_scale)
{
  anastasiev::Rectangle rectangle(2.0, 5.0, {0.0, 0.0});
  BOOST_CHECK_THROW(rectangle.scale(-2.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_triangle_scale)
{
  anastasiev::Triangle triangle({0.0, 0.0}, {0.0, 3.0}, {4.0, 0.0});
  BOOST_CHECK_THROW(triangle.scale(-2.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_circle_scale_area)
{
  anastasiev::Circle circle(5.0, {0.0, 0.0});
  const double circleArea = circle.getArea(), factor = 2.0;
  circle.scale(factor);
  BOOST_CHECK_CLOSE(circleArea * factor * factor, circle.getArea(), ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_recangle_scale_area)
{
  anastasiev::Rectangle rectangle(2.0, 5.0, {0.0, 0.0});
  const double rectangleArea = rectangle.getArea(), factor = 2.0;
  rectangle.scale(factor);
  BOOST_CHECK_CLOSE(rectangleArea * factor * factor, rectangle.getArea(), ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_triangle_scale_area)
{
  anastasiev::Triangle triangle({0.0, 0.0}, {0.0, 3.0}, {4.0, 0.0});
  const double triangleArea = triangle.getArea(), factor = 2.0;
  triangle.scale(factor);
  BOOST_CHECK_CLOSE(triangleArea * factor * factor, triangle.getArea(), ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_circle_move_constancy)
{
  anastasiev::Circle circle(5.0, {0.0, 0.0});
  const double circleArea = circle.getArea();
  anastasiev::rectangle_t circleFrame = circle.getFrameRect();
  circle.move(2.0, -3.0);
  BOOST_CHECK_CLOSE(circleFrame.width, circle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(circleFrame.height, circle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(circleArea, circle.getArea(), ACCURACY);
  circle.move({1.0, 1.0});
  BOOST_CHECK_CLOSE(circleFrame.width, circle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(circleFrame.height, circle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(circleArea, circle.getArea(), ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_rectangle_move_constancy)
{
  anastasiev::Rectangle rectangle(2.0, 5.0, {0.0, 0.0}) ;
  const double rectangleArea = rectangle.getArea();
  anastasiev::rectangle_t rectangleFrame = rectangle.getFrameRect();
  rectangle.move(2.0, -3.0);
  BOOST_CHECK_CLOSE(rectangleFrame.width, rectangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(rectangleFrame.height, rectangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(rectangleArea, rectangle.getArea(), ACCURACY);
  rectangle.move({1.0, 1.0});
  BOOST_CHECK_CLOSE(rectangleFrame.width, rectangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(rectangleFrame.height, rectangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(rectangleArea, rectangle.getArea(), ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_triangle_move_constancy)
{
  anastasiev::Triangle triangle({0.0, 0.0}, {0.0, 3.0}, {4.0, 0.0});
  const double triangleArea = triangle.getArea();
  anastasiev::rectangle_t triangleFrame = triangle.getFrameRect();
  triangle.move(2.0, -3.0);
  BOOST_CHECK_CLOSE(triangleFrame.width, triangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(triangleFrame.height, triangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(triangleArea, triangle.getArea(), ACCURACY);
  triangle.move({1.0, 1.0});
  BOOST_CHECK_CLOSE(triangleFrame.width, triangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(triangleFrame.height, triangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(triangleArea, triangle.getArea(), ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_correct_circle_move)
{
  anastasiev::Circle circle(5.0, {0.0, 0.0});
  const double dx = 3.0, dy= 4.0,
    x = circle.getPosition().x, y = circle.getPosition().y;
  circle.move(dx, dy);
  BOOST_CHECK_CLOSE(circle.getPosition().x, dx + x , ACCURACY);
  BOOST_CHECK_CLOSE(circle.getPosition().y, dy + y , ACCURACY);
  circle.move({dx, dy});
  BOOST_CHECK_CLOSE(circle.getPosition().x, dx, ACCURACY);
  BOOST_CHECK_CLOSE(circle.getPosition().y, dy, ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_correct_rectangle_move)
{
  anastasiev::Rectangle rectangle(2.0, 5.0, {0.0, 0.0});
  const double dx = 3.0, dy= 4.0,
    x = rectangle.getPosition().x, y = rectangle.getPosition().y;
  rectangle.move(dx, dy);
  BOOST_CHECK_CLOSE(rectangle.getPosition().x, dx + x , ACCURACY);
  BOOST_CHECK_CLOSE(rectangle.getPosition().y, dy + y , ACCURACY);
  rectangle.move({dx, dy});
  BOOST_CHECK_CLOSE(rectangle.getPosition().x, dx, ACCURACY);
  BOOST_CHECK_CLOSE(rectangle.getPosition().y, dy, ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_correct_triangle_move)
{
  anastasiev::Triangle triangle({0.0, 0.0}, {0.0, 3.0}, {4.0, 0.0});
  const double dx = 3.0, dy= 4.0,
    x = triangle.getPosition().x, y = triangle.getPosition().y;
  triangle.move(dx, dy);
  BOOST_CHECK_CLOSE(triangle.getPosition().x, dx + x , ACCURACY);
  BOOST_CHECK_CLOSE(triangle.getPosition().y, dy + y , ACCURACY);
  triangle.move({dx, dy});
  BOOST_CHECK_CLOSE(triangle.getPosition().x, dx, ACCURACY);
  BOOST_CHECK_CLOSE(triangle.getPosition().y, dy, ACCURACY);
};
