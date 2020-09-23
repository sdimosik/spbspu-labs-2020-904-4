#define BOOST_TEST_MODULE test
#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double ACCURACY = 0.00001;

BOOST_AUTO_TEST_CASE(test_invalid_index_compositeShape)
{
  kundik::CompositeShape compositeShape(5);
  BOOST_CHECK_THROW(compositeShape[6], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_index_deleted_shape)
{
  kundik::CompositeShape compositeShape(3);
  BOOST_CHECK_THROW(compositeShape.removeShape(4), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_index_compositeShape_adding)
{
  kundik::CompositeShape compositeShape;
  std::shared_ptr<kundik::Shape> shape = nullptr;
  BOOST_CHECK_THROW(compositeShape.addShape(shape), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_scale_composite_shape)
{
  kundik::CompositeShape compositeShape;
  BOOST_CHECK_THROW(compositeShape.scale(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_insert_composite_shape)
{
  kundik::CompositeShape compositeShape(1);
  std::shared_ptr<kundik::Shape> circle = std::make_shared<kundik::Circle>(kundik::Circle({ 5,6 },4));
  compositeShape.addShape(circle);
  BOOST_CHECK(compositeShape[0] == circle);
}

BOOST_AUTO_TEST_CASE(test_get_size_composite_shape)
{
  kundik::CompositeShape compositeShape(1);
  std::shared_ptr<kundik::Shape> circle = std::make_shared<kundik::Circle>(kundik::Circle({ 5,6 }, 4));
  compositeShape.addShape(circle);
  BOOST_CHECK(compositeShape.getSize() == 1);
}

BOOST_AUTO_TEST_CASE(test_getting_total_area)
{
  std::shared_ptr<kundik::Shape> rectangle = std::make_shared<kundik::Rectangle>(kundik::Rectangle({ 4, 5 }, 5, 5));
  std::shared_ptr<kundik::Shape> circle = std::make_shared<kundik::Circle>(kundik::Circle({ 5,6 }, 4));
  kundik::CompositeShape compositeShape(2);
  compositeShape.addShape(rectangle);
  compositeShape.addShape(circle);
  BOOST_CHECK_CLOSE(rectangle->getArea() + circle->getArea(), compositeShape.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_move_composite_shape)
{
  std::shared_ptr<kundik::Shape> rectangle = std::make_shared<kundik::Rectangle>(kundik::Rectangle({ 4, 5 }, 5, 5));
  std::shared_ptr<kundik::Shape> circle = std::make_shared<kundik::Circle>(kundik::Circle({ 5,6 }, 4));
  kundik::CompositeShape compositeShape1(2);
  compositeShape1.addShape(circle);
  compositeShape1.addShape(rectangle);
  const double x = compositeShape1.getCentrer().x;
  const double y = compositeShape1.getCentrer().y;
  const double area = compositeShape1.getArea();

  kundik::CompositeShape compositeShape2(std::move(compositeShape1));
  BOOST_CHECK_CLOSE(x, compositeShape2.getCentrer().x, ACCURACY);
  BOOST_CHECK_CLOSE(y, compositeShape2.getCentrer().y, ACCURACY);
  BOOST_CHECK_CLOSE(area, compositeShape2.getArea(), ACCURACY);

  kundik::CompositeShape compositeShape3;
  compositeShape3 = std::move(compositeShape2);
  BOOST_CHECK_CLOSE(x, compositeShape3.getCentrer().x, ACCURACY);
  BOOST_CHECK_CLOSE(y, compositeShape3.getCentrer().y, ACCURACY);
  BOOST_CHECK_CLOSE(area, compositeShape3.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_correct_composite_shape_moving)
{
  std::shared_ptr<kundik::Shape> rectangle = std::make_shared<kundik::Rectangle>(kundik::Rectangle({ 4, 5 }, 5, 5));
  std::shared_ptr<kundik::Shape> circle = std::make_shared<kundik::Circle>(kundik::Circle({ 5,6 }, 4));
  double rectX = 4;
  double rectY = 5;
  double circleX = 5;
  double circleY = 6;
  kundik::CompositeShape compositeShape(2);
  compositeShape.addShape(rectangle);
  compositeShape.addShape(circle);
  kundik::rectangle_t frameRect = compositeShape.getFrameRect();

  compositeShape.move(1.0, 2.0);
  BOOST_CHECK_CLOSE(frameRect.pos.x + 1.0, compositeShape.getFrameRect().pos.x, ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.pos.y + 2.0, compositeShape.getFrameRect().pos.y, ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.width, compositeShape.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.height, compositeShape.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(rectX += 1.0, compositeShape[0]->getFrameRect().pos.x, ACCURACY);
  BOOST_CHECK_CLOSE(rectY += 2.0, compositeShape[0]->getFrameRect().pos.y, ACCURACY);
  BOOST_CHECK_CLOSE(circleX += 1.0, compositeShape[1]->getFrameRect().pos.x, ACCURACY);
  BOOST_CHECK_CLOSE(circleY += 2.0, compositeShape[1]->getFrameRect().pos.y, ACCURACY);

  double deltaX = 1.0 - compositeShape.getFrameRect().pos.x;
  double deltaY = 1.0 - compositeShape.getFrameRect().pos.y;
  compositeShape.move({ 1.0, 1.0 });
  BOOST_CHECK_CLOSE(1.0, compositeShape.getFrameRect().pos.x, ACCURACY);
  BOOST_CHECK_CLOSE(1.0, compositeShape.getFrameRect().pos.y, ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.width, compositeShape.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.height, compositeShape.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(rectX + deltaX, compositeShape[0]->getFrameRect().pos.x, ACCURACY);
  BOOST_CHECK_CLOSE(rectY + deltaY, compositeShape[0]->getFrameRect().pos.y, ACCURACY);
  BOOST_CHECK_CLOSE(circleX + deltaX, compositeShape[1]->getFrameRect().pos.x, ACCURACY);
  BOOST_CHECK_CLOSE(circleY + deltaY, compositeShape[1]->getFrameRect().pos.y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_copy_composite_shape)
{
  std::shared_ptr<kundik::Shape> circle = std::make_shared<kundik::Circle>(kundik::Circle({ 5,6 },4));
  kundik::CompositeShape compositeShape(1);
  compositeShape.addShape(circle);
  kundik::CompositeShape compositeShape1 = compositeShape;
  BOOST_CHECK_CLOSE(compositeShape[0]->getArea(), compositeShape[0]->getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_getting_center)
{
  std::shared_ptr<kundik::Shape> rectangle = std::make_shared<kundik::Rectangle>(kundik::Rectangle({ 4, 5 }, 5, 5));
  std::shared_ptr<kundik::Shape> circle = std::make_shared<kundik::Circle>(kundik::Circle({ 5,6 }, 4));
  kundik::CompositeShape compositeShape(2);
  compositeShape.addShape(rectangle);
  compositeShape.addShape(circle);
  kundik::rectangle_t frameRect = compositeShape.getFrameRect();
  BOOST_CHECK_CLOSE(frameRect.pos.x, compositeShape.getCentrer().x, ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.pos.y, compositeShape.getCentrer().y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_getting_frame_rectangle)
{
  std::shared_ptr<kundik::Shape> rectangle = std::make_shared<kundik::Rectangle>(kundik::Rectangle({ 0., 0. }, 2., 2.));
  std::shared_ptr<kundik::Shape> circle = std::make_shared<kundik::Circle>(kundik::Circle({ 0., 3. }, 1.));
  kundik::CompositeShape compositeShape(2);
  compositeShape.addShape(rectangle);
  compositeShape.addShape(circle);
  kundik::rectangle_t frameRect;
  frameRect.width = 2.0;
  frameRect.height = 2.0;
  frameRect.pos.x = 0.0;
  frameRect.pos.y = 0;
  BOOST_CHECK_CLOSE(frameRect.pos.x, compositeShape.getFrameRect().pos.x, ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.pos.y, compositeShape.getFrameRect().pos.y, ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.width, compositeShape.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.height, compositeShape.getFrameRect().height, ACCURACY);
}
