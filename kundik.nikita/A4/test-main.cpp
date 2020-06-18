#define BOOST_TEST_MODULE test
#define _USE_MATH_DEFINES

#include <cmath>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

const double ACCURACY = 0.00001;

BOOST_AUTO_TEST_CASE(test_rotate_circle)
{
  kundik::Circle circle({ 0.0, 0.0 }, 3.0);
  const double area = circle.getArea();
  kundik::point_t center;
  center.x = circle.getCenterX();
  center.y = circle.getCenterY();
  circle.rotate(40.0);
  BOOST_CHECK_CLOSE(area, circle.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(center.x, circle.getCenterX(), ACCURACY);
  BOOST_CHECK_CLOSE(center.y, circle.getCenterY(), ACCURACY);
}
BOOST_AUTO_TEST_CASE(test_invalid_rotate_rectangle)
{
  kundik::Rectangle rectangle({{0.0, 0.0}, 3.0, 3.0});
  const double area = rectangle.getArea();
  kundik::point_t center;
  center.x = rectangle.getCenterX();
  center.y = rectangle.getCenterY();
  double angle = 45;
  rectangle.rotate(angle);
  BOOST_CHECK_CLOSE(area, rectangle.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(center.x, rectangle.getCenterX(), ACCURACY);
  BOOST_CHECK_CLOSE(center.y, rectangle.getCenterY(), ACCURACY);
  BOOST_CHECK_CLOSE(rectangle.getCenterX(), rectangle.getFrameRect().pos.x, ACCURACY);
  BOOST_CHECK_CLOSE(rectangle.getCenterY(), rectangle.getFrameRect().pos.y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_invalid_rotate_compositeShape)
{
  kundik::CompositeShape compositeShape(2);
  std::shared_ptr<kundik::Shape> circle = std::make_shared<kundik::Circle>(kundik::Circle({ 2.0, 2.0 }, 2.0));
  std::shared_ptr<kundik::Shape> rectangle = std::make_shared<kundik::Rectangle>(kundik::Rectangle({ 2.0, 7.0 }, 4.0, 2.0));
  compositeShape.addShape(circle);
  compositeShape.addShape(rectangle);
  double commonArea = compositeShape.getArea();
  double angle = 30;
  compositeShape.rotate(3 * angle);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), commonArea, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, 2, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, 4, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_empty_shape_add_shape)
{
  kundik::Matrix matrix;
  std::shared_ptr<kundik::Shape> shape = nullptr;
  BOOST_CHECK_THROW(matrix.addShape(shape), std::invalid_argument);
}
