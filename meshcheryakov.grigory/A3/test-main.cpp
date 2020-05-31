#define BOOST_TEST_MODULE LAB_A3

#include <memory>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

const double ACCURACY = 0.00001;

BOOST_AUTO_TEST_CASE(test_invalid_index_compositeShape)
{
  meshcheryakov::CompositeShape compositeShape;
  BOOST_CHECK_THROW(compositeShape[0], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_coefficient_scale)
{
  meshcheryakov::Rectangle rectangle({2.0, 2.0, { 3.0, 3.0 }});
  std::shared_ptr<meshcheryakov::Shape> shape = std::make_shared<meshcheryakov::Rectangle>(rectangle);
  meshcheryakov::CompositeShape compositeShape(1);
  compositeShape.addShape(shape);
  BOOST_CHECK_THROW(compositeShape.scale(-3.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_getArea)
{
  meshcheryakov::Circle circle (5.0, {0.0, 0.0});
  meshcheryakov::Rectangle rectangle ({6.0, 6.0, {10.0, 10.0}});
  std::shared_ptr<meshcheryakov::Shape> shape1 = std::make_shared<meshcheryakov::Circle>(circle);
  std::shared_ptr<meshcheryakov::Shape> shape2 = std::make_shared<meshcheryakov::Rectangle>(rectangle);
  meshcheryakov::CompositeShape compositeShape(1);
  compositeShape.addShape(shape1);
  compositeShape.addShape(shape2);
  double sum = shape1->getArea() + shape2->getArea();
  BOOST_CHECK_CLOSE(sum, compositeShape.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_getFrameRect)
{
  meshcheryakov::CompositeShape compositeShape(2);
  meshcheryakov::Circle circle({2.0,  {0.0, 6.0}});
  meshcheryakov::Rectangle rectangle({4.0, 4.0, {0.0, 0.0}});
  std::shared_ptr<meshcheryakov::Shape> shape1 = std::make_shared<meshcheryakov::Circle>(circle);
  std::shared_ptr<meshcheryakov::Shape> shape2 = std::make_shared<meshcheryakov::Rectangle>(rectangle);
  compositeShape.addShape(shape1);
  compositeShape.addShape(shape2);
  double width = 4.0;
  double height = 10.0;
  double x = 0.0;
  double y = 3.0;
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, width, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, height, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, x, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_copying_composite_shape)
{
  meshcheryakov::CompositeShape compositeShape(2);
  meshcheryakov::Circle circle({6.0,  {2.0, 2.0}});
  meshcheryakov::Rectangle rectangle({4.0, 4.0, {5.0, 5.0}});
  std::shared_ptr<meshcheryakov::Shape> shape1 = std::make_shared<meshcheryakov::Circle>(circle);
  std::shared_ptr<meshcheryakov::Shape> shape2 = std::make_shared<meshcheryakov::Rectangle>(rectangle);
  compositeShape.addShape(shape1);
  compositeShape.addShape(shape2);
  meshcheryakov::CompositeShape compositeShape1(compositeShape);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), compositeShape1.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getPosition().x, compositeShape1.getPosition().x, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getPosition().y, compositeShape1.getPosition().y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_move)
{
  meshcheryakov::Circle circle({6.0,  {2.0, 2.0}});
  meshcheryakov::Rectangle rectangle({4.0, 4.0, {5.0, 5.0}});
  std::shared_ptr<meshcheryakov::Shape> shape1 = std::make_shared<meshcheryakov::Circle>(circle);
  std::shared_ptr<meshcheryakov::Shape> shape2 = std::make_shared<meshcheryakov::Rectangle>(rectangle);
  meshcheryakov::CompositeShape compositeShape(2);
  compositeShape.addShape(shape1);
  compositeShape.addShape(shape2);

  const double x1 = 2.0;
  const double y1 = 2.0;
  const double x2 = 3.0;
  const double y2 = 3.0;
  const double circleArea = compositeShape[0]->getArea();
  const double rectArea = compositeShape[1]->getArea();
  const double area = compositeShape.getArea();
  const double frameH = compositeShape.getFrameRect().height;
  const double frameW = compositeShape.getFrameRect().width;

  compositeShape.move(x1, y1);
  BOOST_CHECK_CLOSE(compositeShape[0]->getArea(), circleArea, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape[1]->getArea(), rectArea, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), area, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, frameH, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, frameW, ACCURACY);

  compositeShape.move(meshcheryakov::point_t{x2, y2});
  BOOST_CHECK_CLOSE(compositeShape[0]->getArea(), circleArea, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape[1]->getArea(), rectArea, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), area, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, frameH, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, frameW, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_invalid_composite_addShape)
{
  meshcheryakov::CompositeShape compositeShape;
  BOOST_CHECK_THROW(compositeShape.addShape(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_composite_removeShape)
{
  meshcheryakov::CompositeShape compositeShape;
  BOOST_CHECK_THROW(compositeShape.removeShape(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_addShape)
{
  meshcheryakov::Circle circle({6.0,  {2.0, 2.0}});
  std::shared_ptr<meshcheryakov::Shape> shape = std::make_shared<meshcheryakov::Circle>(circle);
  meshcheryakov::CompositeShape compositeShape;
  compositeShape.addShape(shape);
  BOOST_CHECK(compositeShape[0] == shape);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_removeShape)
{
  meshcheryakov::CompositeShape compositeShape(2);
  meshcheryakov::Circle circle(6.0,  {2.0, 2.0});
  meshcheryakov::Rectangle rectangle({4.0, 4.0, {5.0, 5.0}});
  std::shared_ptr<meshcheryakov::Shape> shape1 = std::make_shared<meshcheryakov::Circle>(circle);
  std::shared_ptr<meshcheryakov::Shape> shape2 = std::make_shared<meshcheryakov::Rectangle>(rectangle);
  compositeShape.addShape(shape1);
  compositeShape.addShape(shape2);
  BOOST_CHECK(compositeShape.getSize() == 2);
  compositeShape.removeShape(1);
  BOOST_CHECK(compositeShape.getSize() == 1);
  compositeShape.removeShape(0);
  BOOST_CHECK(compositeShape.getSize() == 0);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_scale)
{
  meshcheryakov::CompositeShape compositeShape(2);
  meshcheryakov::Circle circle({6.0,  {2.0, 2.0}});
  meshcheryakov::Rectangle rectangle({4.0, 4.0, {5.0, 5.0}});
  std::shared_ptr<meshcheryakov::Shape> shape1 = std::make_shared<meshcheryakov::Circle>(circle);
  std::shared_ptr<meshcheryakov::Shape> shape2 = std::make_shared<meshcheryakov::Rectangle>(rectangle);
  compositeShape.addShape(shape1);
  compositeShape.addShape(shape2);

  const double circleArea = circle.getArea();
  const double rectArea = rectangle.getArea();
  const double area = compositeShape.getArea();

  compositeShape.scale(2.0);
  BOOST_CHECK_CLOSE(circleArea * 2.0 * 2.0, compositeShape[0]->getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(rectArea * 2.0 * 2.0, compositeShape[1]->getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(area * 2.0 * 2.0, compositeShape.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_getCenter)
{
  meshcheryakov::CompositeShape compositeShape(2);
  meshcheryakov::Circle circle({6.0,  {2.0, 2.0}});
  meshcheryakov::Rectangle rectangle({4.0, 4.0, {5.0, 5.0}});
  std::shared_ptr<meshcheryakov::Shape> shape1 = std::make_shared<meshcheryakov::Circle>(circle);
  std::shared_ptr<meshcheryakov::Shape> shape2 = std::make_shared<meshcheryakov::Rectangle>(rectangle);
  compositeShape.addShape(shape1);
  compositeShape.addShape(shape2);
  meshcheryakov::rectangle_t frame = compositeShape.getFrameRect();
  BOOST_CHECK_CLOSE(frame.pos.x, compositeShape.getPosition().x, ACCURACY);
  BOOST_CHECK_CLOSE(frame.pos.y, compositeShape.getPosition().y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_getSize)
{
  meshcheryakov::CompositeShape compositeShape(2);
  meshcheryakov::Circle circle({6.0,  {2.0, 2.0}});
  meshcheryakov::Rectangle rectangle({4.0, 4.0, {5.0, 5.0}});
  std::shared_ptr<meshcheryakov::Shape> shape1 = std::make_shared<meshcheryakov::Circle>(circle);
  std::shared_ptr<meshcheryakov::Shape> shape2 = std::make_shared<meshcheryakov::Rectangle>(rectangle);
  compositeShape.addShape(shape1);
  compositeShape.addShape(shape2);
  BOOST_CHECK(compositeShape.getSize() == 2);
}
