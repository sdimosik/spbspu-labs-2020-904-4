#define BOOST_TEST_MODULE test

#include <memory>
#include <boost/test/tools/floating_point_comparison.hpp>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

const double ACCURACY = 0.0001;

BOOST_AUTO_TEST_CASE(test_invalid_index_reference_composite_shape)
{
  khilchenko::CompositeShape compositeShape(2);
  BOOST_CHECK_THROW(compositeShape[-1], std::out_of_range);
  BOOST_CHECK_THROW(compositeShape[3], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_frame_rectangle_empty_composite_shape)
{
  khilchenko::CompositeShape compositeShape(2);
  BOOST_CHECK_THROW(compositeShape.getFrameRect(), std::logic_error);
}

BOOST_AUTO_TEST_CASE(test_invalid_coefficient_scale_composite_shape)
{
  khilchenko::CompositeShape compositeShape(2);
  BOOST_CHECK_THROW(compositeShape.scale(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_shape_ptr_composite_shape)
{
  khilchenko::CompositeShape compositeShape(2);
  std::shared_ptr<khilchenko::Shape> shape = nullptr;
  BOOST_CHECK_THROW(compositeShape.addShape(shape), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_index_remove_composite_shape)
{
  khilchenko::CompositeShape compositeShape(2);
  BOOST_CHECK_THROW(compositeShape.removeShape(-1), std::out_of_range);
  BOOST_CHECK_THROW(compositeShape.removeShape(5), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_addShape_composite_shape)
{
  khilchenko::CompositeShape compositeShape(2);
  std::shared_ptr<khilchenko::Shape> circle = std::make_shared<khilchenko::Circle>(khilchenko::Circle(9, {0, 0}));
  compositeShape.addShape(circle);
  BOOST_CHECK(compositeShape[0] == circle);
}

BOOST_AUTO_TEST_CASE(test_removeShape_composite_shape)
{
  khilchenko::CompositeShape compositeShape(2);
  std::shared_ptr<khilchenko::Shape> circle = std::make_shared<khilchenko::Circle>(khilchenko::Circle(9, {0, 0}));
  std::shared_ptr<khilchenko::Shape> rectangle = std::make_shared<khilchenko::Rectangle>(khilchenko::Rectangle(9, 10, {5, 25}));
  compositeShape.addShape(circle);
  compositeShape.addShape(rectangle);
  compositeShape.removeShape(0);
  BOOST_CHECK(compositeShape.getAmount() == 1);
  BOOST_CHECK(compositeShape[0] == rectangle);
}

BOOST_AUTO_TEST_CASE(test_getArea_composite_shape)
{
  khilchenko::CompositeShape compositeShape(2);
  khilchenko::Circle circle (9, {0, 0});
  khilchenko::Rectangle rectangle (9, 2, {12, 2});
  std::shared_ptr<khilchenko::Shape> compositeCircle = std::make_shared<khilchenko::Circle>(circle);
  std::shared_ptr<khilchenko::Shape> compositeRectangle = std::make_shared<khilchenko::Rectangle>(rectangle);
  compositeShape.addShape(compositeCircle);
  compositeShape.addShape(compositeRectangle);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), (circle.getArea() + rectangle.getArea()), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_getFrameRect_composite_shape)
{
  khilchenko::CompositeShape compositeShape(2);
  khilchenko::Circle circle (9, {0, 0});
  khilchenko::Rectangle rectangle (9, 2, {25, 0});
  std::shared_ptr<khilchenko::Shape> compositeCircle = std::make_shared<khilchenko::Circle>(circle);
  std::shared_ptr<khilchenko::Shape> compositeRectangle = std::make_shared<khilchenko::Rectangle>(rectangle);
  compositeShape.addShape(compositeCircle);
  compositeShape.addShape(compositeRectangle);
  double upperLimit = 9;
  double lowerLimit = -9;
  double rightLimit = 29.5;
  double leftLimit = -9;
  BOOST_CHECK(compositeShape.getAmount() == 2);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, (upperLimit - lowerLimit), ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, (rightLimit - leftLimit), ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, (leftLimit + rightLimit) / 2, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, (upperLimit + lowerLimit) / 2, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_getCenter_composite_shape)
{
  khilchenko::CompositeShape compositeShape(2);
  khilchenko::Circle circle (9, {0, 0});
  khilchenko::Rectangle rectangle (9, 2, {25, 0});
  std::shared_ptr<khilchenko::Shape> compositeCircle = std::make_shared<khilchenko::Circle>(circle);
  std::shared_ptr<khilchenko::Shape> compositeRectangle = std::make_shared<khilchenko::Rectangle>(rectangle);
  compositeShape.addShape(compositeCircle);
  compositeShape.addShape(compositeRectangle);
  double upperLimit = 9;
  double lowerLimit = -9;
  double rightLimit = 29.5;
  double leftLimit = -9;
  BOOST_CHECK_CLOSE(compositeShape.getCenter().x, (leftLimit + rightLimit) / 2, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getCenter().y, (upperLimit + lowerLimit) / 2, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_move_newPos_composite_shape)
{
  khilchenko::CompositeShape compositeShape(2);
  std::shared_ptr<khilchenko::Shape> circle = std::make_shared<khilchenko::Circle>(khilchenko::Circle(9, {0, 0}));
  std::shared_ptr<khilchenko::Shape> rectangle = std::make_shared<khilchenko::Rectangle>(khilchenko::Rectangle(9, 2, {12, 2}));
  compositeShape.addShape(circle);
  compositeShape.addShape(rectangle);
  double startX = compositeShape.getFrameRect().pos.x;
  double startY = compositeShape.getFrameRect().pos.y;
  khilchenko::point_t newPos{100, 100};
  double deltaX = 100 - startX;
  double deltaY = 100 - startY;
  compositeShape.move(newPos);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, (startX + deltaX), ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, (startY + deltaY), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_move_increase_composite_shape)
{
  khilchenko::CompositeShape compositeShape(2);
  std::shared_ptr<khilchenko::Shape> circle = std::make_shared<khilchenko::Circle>(khilchenko::Circle(9, {0, 0}));
  std::shared_ptr<khilchenko::Shape> rectangle = std::make_shared<khilchenko::Rectangle>(khilchenko::Rectangle(9, 2, {12, 2}));
  compositeShape.addShape(circle);
  compositeShape.addShape(rectangle);
  double startX = compositeShape.getFrameRect().pos.x;
  double startY = compositeShape.getFrameRect().pos.y;
  double deltaX = 25;
  double deltaY = 35;
  compositeShape.move(deltaX, deltaY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, (startX + deltaX), ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, (startY + deltaY), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_immutability_move_composite_shape)
{
  khilchenko::CompositeShape compositeShape(2);
  std::shared_ptr<khilchenko::Shape> circle = std::make_shared<khilchenko::Circle>(khilchenko::Circle(9, {0, 0}));
  std::shared_ptr<khilchenko::Shape> rectangle = std::make_shared<khilchenko::Rectangle>(khilchenko::Rectangle(9, 2, {12, 2}));
  compositeShape.addShape(circle);
  compositeShape.addShape(rectangle);
  double startArea = compositeShape.getArea();
  khilchenko::point_t newPos{100, 100};
  compositeShape.move(newPos);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), startArea, ACCURACY);
  compositeShape.move(25, 35);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), startArea, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_scale_composite_shape)
{
  khilchenko::CompositeShape compositeShape(2);
  std::shared_ptr<khilchenko::Shape> circle = std::make_shared<khilchenko::Circle>(khilchenko::Circle(9, {0, 0}));
  std::shared_ptr<khilchenko::Shape> rectangle = std::make_shared<khilchenko::Rectangle>(khilchenko::Rectangle(9, 2, {12, 2}));
  compositeShape.addShape(circle);
  compositeShape.addShape(rectangle);
  double coefficient = 2;
  double startArea = compositeShape.getArea();
  compositeShape.scale(coefficient);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), startArea * 4, ACCURACY);
}
