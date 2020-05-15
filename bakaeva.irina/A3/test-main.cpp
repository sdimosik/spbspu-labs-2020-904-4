#define BOOST_TEST_MODULE myTest

#include <boost/test/included/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>
#include <memory>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double TOLERANCE_RANGE = 0.00001;

BOOST_AUTO_TEST_CASE(test_invalid_index_composite_shape)
{
  bakaeva::CompositeShape compositeShape;
  BOOST_CHECK_THROW(compositeShape[0], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_coefficient_scaling_rectangle)
{
  bakaeva::Rectangle rectangle(3.1, 4.8, { 0.4, 5.0 });
  bakaeva::CompositeShape::shapePtr shape = std::make_shared<bakaeva::Rectangle>(rectangle);
  bakaeva::CompositeShape compositeShape(1);
  compositeShape.addShape(shape);
  BOOST_CHECK_THROW(compositeShape.scale(-2.3), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_pointer_added_shape)
{
  bakaeva::CompositeShape compositeShape;
  bakaeva::CompositeShape::shapePtr shape = nullptr;
  BOOST_CHECK_THROW(compositeShape.addShape(shape), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_index_deleted_shape)
{
  bakaeva::CompositeShape compositeShape;
  BOOST_CHECK_THROW(compositeShape.removeShape(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_copying_composite_shape)
{
  bakaeva::Rectangle rectangle(3.1, 4.8, { 0.4, 5.0 });
  bakaeva::Circle circle(5, { 4.6, 7.0 });
  bakaeva::CompositeShape::shapePtr shape1 = std::make_shared<bakaeva::Rectangle>(rectangle);
  bakaeva::CompositeShape::shapePtr shape2 = std::make_shared<bakaeva::Circle>(circle);
  bakaeva::CompositeShape compositeShape1(2);
  compositeShape1.addShape(shape1);
  compositeShape1.addShape(shape2);
  bakaeva::CompositeShape compositeShape2(compositeShape1);
  BOOST_CHECK_CLOSE(compositeShape1.getCenter().x, compositeShape2.getCenter().x, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(compositeShape1.getCenter().y, compositeShape2.getCenter().y, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(compositeShape1.getArea(), compositeShape2.getArea(), TOLERANCE_RANGE);

  bakaeva::CompositeShape compositeShape3;
  compositeShape3 = compositeShape1;
  BOOST_CHECK_CLOSE(compositeShape1.getCenter().x, compositeShape3.getCenter().x, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(compositeShape1.getCenter().y, compositeShape3.getCenter().y, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(compositeShape1.getArea(), compositeShape3.getArea(), TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_moving_composite_shape)
{
  bakaeva::Rectangle rectangle(3.1, 4.8, { 0.4, 5.0 });
  bakaeva::Circle circle(5, { 4.6, 7.0 });
  bakaeva::CompositeShape::shapePtr shape1 = std::make_shared<bakaeva::Rectangle>(rectangle);
  bakaeva::CompositeShape::shapePtr shape2 = std::make_shared<bakaeva::Circle>(circle);
  bakaeva::CompositeShape compositeShape1(2);
  compositeShape1.addShape(shape1);
  compositeShape1.addShape(shape2);

  const double x = compositeShape1.getCenter().x;
  const double y = compositeShape1.getCenter().y;
  const double area = compositeShape1.getArea();

  bakaeva::CompositeShape compositeShape2(std::move(compositeShape1));
  BOOST_CHECK_CLOSE(x, compositeShape2.getCenter().x, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(y, compositeShape2.getCenter().y, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(area, compositeShape2.getArea(), TOLERANCE_RANGE);

  bakaeva::CompositeShape compositeShape3;
  compositeShape3 = std::move(compositeShape2);
  BOOST_CHECK_CLOSE(x, compositeShape3.getCenter().x, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(y, compositeShape3.getCenter().y, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(area, compositeShape3.getArea(), TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_getting_total_area)
{
  bakaeva::Rectangle rectangle(3.1, 4.8, { 0.4, 5.0 });
  bakaeva::Circle circle(5, { 4.6, 7.0 });
  bakaeva::CompositeShape::shapePtr shape1 = std::make_shared<bakaeva::Rectangle>(rectangle);
  bakaeva::CompositeShape::shapePtr shape2 = std::make_shared<bakaeva::Circle>(circle);
  bakaeva::CompositeShape compositeShape(2);
  compositeShape.addShape(shape1);
  compositeShape.addShape(shape2);
  BOOST_CHECK_CLOSE(shape1->getArea() + shape2->getArea(), compositeShape.getArea(), TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_getting_frame_rectangle)
{
  bakaeva::Rectangle rectangle(2.0, 2.0, { 0.0, 0.0 });
  bakaeva::Circle circle(1.0, { 0.0, 3.0 });
  bakaeva::CompositeShape::shapePtr shape1 = std::make_shared<bakaeva::Rectangle>(rectangle);
  bakaeva::CompositeShape::shapePtr shape2 = std::make_shared<bakaeva::Circle>(circle);
  bakaeva::CompositeShape compositeShape(2);
  compositeShape.addShape(shape1);
  compositeShape.addShape(shape2);
  bakaeva::rectangle_t frameRect;
  frameRect.width = 2.0;
  frameRect.height = 5.0;
  frameRect.pos.x = 0.0;
  frameRect.pos.y = 1.5;
  BOOST_CHECK_CLOSE(frameRect.pos.x, compositeShape.getFrameRect().pos.x, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.pos.y, compositeShape.getFrameRect().pos.y, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.width, compositeShape.getFrameRect().width, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.height, compositeShape.getFrameRect().height, TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_correct_composite_shape_moving)
{
  bakaeva::Rectangle rectangle(3.1, 4.8, { 0.4, 5.0 });
  double rectX = 0.4;
  double rectY = 5.0;
  bakaeva::Circle circle(5, { 4.6, 7.0 });
  double circleX = 4.6;
  double circleY = 7.0;
  bakaeva::CompositeShape::shapePtr shape1 = std::make_shared<bakaeva::Rectangle>(rectangle);
  bakaeva::CompositeShape::shapePtr shape2 = std::make_shared<bakaeva::Circle>(circle);
  bakaeva::CompositeShape compositeShape(2);
  compositeShape.addShape(shape1);
  compositeShape.addShape(shape2);
  bakaeva::rectangle_t frameRect = compositeShape.getFrameRect();

  compositeShape.move(1.0, 2.0);
  BOOST_CHECK_CLOSE(frameRect.pos.x + 1.0, compositeShape.getFrameRect().pos.x, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.pos.y + 2.0, compositeShape.getFrameRect().pos.y, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.width, compositeShape.getFrameRect().width, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.height, compositeShape.getFrameRect().height, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(rectX += 1.0, compositeShape[0]->getFrameRect().pos.x, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(rectY += 2.0, compositeShape[0]->getFrameRect().pos.y, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(circleX += 1.0, compositeShape[1]->getFrameRect().pos.x, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(circleY += 2.0, compositeShape[1]->getFrameRect().pos.y, TOLERANCE_RANGE);

  double deltaX = 1.0 - compositeShape.getFrameRect().pos.x;
  double deltaY = 1.0 - compositeShape.getFrameRect().pos.y;
  compositeShape.move({ 1.0, 1.0 });
  BOOST_CHECK_CLOSE(1.0, compositeShape.getFrameRect().pos.x, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(1.0, compositeShape.getFrameRect().pos.y, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.width, compositeShape.getFrameRect().width, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.height, compositeShape.getFrameRect().height, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(rectX + deltaX, compositeShape[0]->getFrameRect().pos.x, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(rectY + deltaY, compositeShape[0]->getFrameRect().pos.y, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(circleX + deltaX, compositeShape[1]->getFrameRect().pos.x, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(circleY + deltaY, compositeShape[1]->getFrameRect().pos.y, TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_scaling)
{
  bakaeva::Rectangle rectangle(3.1, 4.8, { 0.4, 5.0 });
  bakaeva::Circle circle(5, { 4.6, 7.0 });
  double rectArea = rectangle.getArea();
  double circleArea = circle.getArea();
  bakaeva::CompositeShape::shapePtr shape1 = std::make_shared<bakaeva::Rectangle>(rectangle);
  bakaeva::CompositeShape::shapePtr shape2 = std::make_shared<bakaeva::Circle>(circle);
  bakaeva::CompositeShape compositeShape(2);
  compositeShape.addShape(shape1);
  compositeShape.addShape(shape2);
  double totalArea = compositeShape.getArea();
  const double coefficient1 = 1.5;
  const double coefficient2 = 0.5;
  compositeShape.scale(coefficient1);
  BOOST_CHECK_CLOSE(rectArea * coefficient1 * coefficient1, compositeShape[0]->getArea(), TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(circleArea * coefficient1 * coefficient1, compositeShape[1]->getArea(), TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(totalArea * coefficient1 * coefficient1, compositeShape.getArea(), TOLERANCE_RANGE);

  rectArea = compositeShape[0]->getArea();
  circleArea =  compositeShape[1]->getArea();
  totalArea = compositeShape.getArea();
  compositeShape.scale(coefficient2);
  BOOST_CHECK_CLOSE(rectArea * coefficient2 * coefficient2, compositeShape[0]->getArea(), TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(circleArea * coefficient2 * coefficient2, compositeShape[1]->getArea(), TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(totalArea * coefficient2 * coefficient2, compositeShape.getArea(), TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_getting_size)
{
  bakaeva::Rectangle rectangle(3.1, 4.8, { 0.4, 5.0 });
  bakaeva::Circle circle(5, { 4.6, 7.0 });
  bakaeva::CompositeShape::shapePtr shape1 = std::make_shared<bakaeva::Rectangle>(rectangle);
  bakaeva::CompositeShape::shapePtr shape2 = std::make_shared<bakaeva::Circle>(circle);
  bakaeva::CompositeShape compositeShape(2);
  compositeShape.addShape(shape1);
  compositeShape.addShape(shape2);
  BOOST_CHECK(2 == compositeShape.getSize());
}

BOOST_AUTO_TEST_CASE(test_getting_center)
{
  bakaeva::Rectangle rectangle(3.1, 4.8, { 0.4, 5.0 });
  bakaeva::Circle circle(5, { 4.6, 7.0 });
  bakaeva::CompositeShape::shapePtr shape1 = std::make_shared<bakaeva::Rectangle>(rectangle);
  bakaeva::CompositeShape::shapePtr shape2 = std::make_shared<bakaeva::Circle>(circle);
  bakaeva::CompositeShape compositeShape(2);
  compositeShape.addShape(shape1);
  compositeShape.addShape(shape2);
  bakaeva::rectangle_t frameRect = compositeShape.getFrameRect();
  BOOST_CHECK_CLOSE(frameRect.pos.x, compositeShape.getCenter().x, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.pos.y, compositeShape.getCenter().y, TOLERANCE_RANGE);
}
