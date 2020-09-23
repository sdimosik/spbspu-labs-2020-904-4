#define BOOST_TEST_MODULE A3test

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "../common/composite-shape.hpp"
#include "../common/circle.hpp"
#include "../common/rectangle.hpp"

const double ACCURACY = 0.0000001;

BOOST_AUTO_TEST_CASE(test_composite_shape_invalid_index)
{
  stolyarov::CompositeShape compositeShape;
  BOOST_CHECK_THROW(compositeShape[-1], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_invalid_index_deliting)
{
  stolyarov::CompositeShape compositeShape;
  BOOST_CHECK_THROW(compositeShape.removeElement(2), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_invalid_index_adding)
{
  stolyarov::CompositeShape compositeShape;
  stolyarov::CompositeShape::shapePtr shape = nullptr;
  BOOST_CHECK_THROW(compositeShape.addElement(shape), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_invalid_rate_scaling)
{
  stolyarov::CompositeShape compositeShape;
  stolyarov::Rectangle rectangle(5.1, 2.3, { 12.4, 5.4 });
  stolyarov::CompositeShape::shapePtr shape = std::make_shared<stolyarov::Rectangle>(rectangle);
  compositeShape.addElement(shape);
  BOOST_CHECK_THROW(compositeShape.scale(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_permanency_moving_by_coordinates)
{
  double width = 23.4;
  double height = 12.3;
  double radius = 7.7;
  double dx = 15.2;
  double dy = -21.1;

  stolyarov::point_t rectPos{ 5.5, -13.9 };
  stolyarov::point_t circlePos{ -19.5, 3.1 };

  stolyarov::CompositeShape compositeShape;
  stolyarov::Rectangle rctngl(width, height, rectPos);
  stolyarov::CompositeShape::shapePtr shape1 = std::make_shared<stolyarov::Rectangle>(rctngl);
  compositeShape.addElement(shape1);
  stolyarov::Circle crkl(radius, circlePos);
  stolyarov::CompositeShape::shapePtr shape2 = std::make_shared<stolyarov::Circle>(crkl);
  compositeShape.addElement(shape2);

  stolyarov::point_t finalPos = compositeShape.getCenter();
  finalPos.x += dx;
  finalPos.y += dy;

  stolyarov::point_t rectFinalPos = rectPos;
  rectFinalPos.x += dx;
  rectFinalPos.y += dy;

  stolyarov::point_t circleFinalPos = circlePos;
  circleFinalPos.x += dx;
  circleFinalPos.y += dy;

  compositeShape.move(dx, dy);

  stolyarov::point_t posAfterMove = compositeShape.getCenter();

  BOOST_CHECK_CLOSE(posAfterMove.x, finalPos.x, ACCURACY);
  BOOST_CHECK_CLOSE(posAfterMove.y, finalPos.y, ACCURACY);

  BOOST_CHECK_CLOSE(rectFinalPos.x, compositeShape[0]->getCenter().x, ACCURACY);
  BOOST_CHECK_CLOSE(rectFinalPos.y, compositeShape[0]->getCenter().y, ACCURACY);

  BOOST_CHECK_CLOSE(circleFinalPos.y, compositeShape[1]->getCenter().y, ACCURACY);
  BOOST_CHECK_CLOSE(circleFinalPos.x, compositeShape[1]->getCenter().x, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_permanency_moving_to_point)
{
  double width = 23.4;
  double height = 12.3;
  double radius = 7.7;
  stolyarov::point_t rectPos{ 5.5, -13.9 };
  stolyarov::point_t circlePos{ -19.5, 3.1 };
  stolyarov::point_t newPos{ 15.2, -21.1 };

  stolyarov::CompositeShape compositeShape;
  stolyarov::Rectangle rctngl(width, height, rectPos);
  stolyarov::CompositeShape::shapePtr shape1 = std::make_shared<stolyarov::Rectangle>(rctngl);
  compositeShape.addElement(shape1);
  stolyarov::Circle crkl(radius, circlePos);
  stolyarov::CompositeShape::shapePtr shape2 = std::make_shared<stolyarov::Circle>(crkl);
  compositeShape.addElement(shape2);

  stolyarov::point_t prevPos = compositeShape.getCenter();

  stolyarov::point_t rectFinalPos = rectPos;
  rectFinalPos.x += newPos.x - prevPos.x;
  rectFinalPos.y += newPos.y - prevPos.y;

  stolyarov::point_t circleFinalPos = circlePos;
  circleFinalPos.x += newPos.x - prevPos.x;
  circleFinalPos.y += newPos.y - prevPos.y;

  compositeShape.move(newPos);

  stolyarov::point_t posAfterMove = compositeShape.getCenter();

  BOOST_CHECK_CLOSE(posAfterMove.x, newPos.x, ACCURACY);
  BOOST_CHECK_CLOSE(posAfterMove.y, newPos.y, ACCURACY);

  BOOST_CHECK_CLOSE(rectFinalPos.x, compositeShape[0]->getCenter().x, ACCURACY);
  BOOST_CHECK_CLOSE(rectFinalPos.y, compositeShape[0]->getCenter().y, ACCURACY);

  BOOST_CHECK_CLOSE(circleFinalPos.y, compositeShape[1]->getCenter().y, ACCURACY);
  BOOST_CHECK_CLOSE(circleFinalPos.x, compositeShape[1]->getCenter().x, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_coping)
{
  stolyarov::Circle circle(5, { 4.6, 7.0 });
  stolyarov::CompositeShape::shapePtr shape1 = std::make_shared<stolyarov::Circle>(circle);
  stolyarov::Rectangle rectangle(2.3, 1.3, { 12.3, 1.2 });
  stolyarov::CompositeShape::shapePtr shape2 = std::make_shared<stolyarov::Rectangle>(rectangle);

  stolyarov::CompositeShape compositeShape1;
  compositeShape1.addElement(shape1);
  compositeShape1.addElement(shape2);
  stolyarov::CompositeShape compositeShape2(compositeShape1);
  BOOST_CHECK_CLOSE(compositeShape1.getCenter().x, compositeShape2.getCenter().x, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape1.getCenter().y, compositeShape2.getCenter().y, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape1.getArea(), compositeShape2.getArea(), ACCURACY);

  stolyarov::CompositeShape compositeShape3;
  compositeShape3 = compositeShape1;
  BOOST_CHECK_CLOSE(compositeShape3.getCenter().x, compositeShape1.getCenter().x, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape3.getCenter().y, compositeShape1.getCenter().y, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape3.getArea(), compositeShape1.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_valid_common_area)
{
  stolyarov::Rectangle rectangle(23.1, 43.1, { 12.1, 5.1 });
  stolyarov::Circle circle(5.11, { 1.1, 2.1 });
  stolyarov::CompositeShape::shapePtr shape1 = std::make_shared<stolyarov::Rectangle>(rectangle);
  stolyarov::CompositeShape::shapePtr shape2 = std::make_shared<stolyarov::Circle>(circle);
  stolyarov::CompositeShape compositeShape;
  compositeShape.addElement(shape1);
  compositeShape.addElement(shape2);
  BOOST_CHECK_CLOSE(shape1->getArea() + shape2->getArea(), compositeShape.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_getting_frame_rec)
{
  stolyarov::Rectangle rectangle(2.0, 5.0, { 3.0, 3.0 });
  stolyarov::Circle circle(1.0, { -1.0, 0.0 });
  stolyarov::CompositeShape::shapePtr shape1 = std::make_shared<stolyarov::Rectangle>(rectangle);
  stolyarov::CompositeShape::shapePtr shape2 = std::make_shared<stolyarov::Circle>(circle);
  stolyarov::CompositeShape compositeShape;
  compositeShape.addElement(shape1);
  compositeShape.addElement(shape2);
  stolyarov::rectangle_t frameRect;
  frameRect.width = 6.0;
  frameRect.height = 6.5;
  frameRect.pos.x = 1.0;
  frameRect.pos.y = 2.25;
  BOOST_CHECK_CLOSE(frameRect.pos.x, compositeShape.getFrameRect().pos.x, ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.pos.y, compositeShape.getFrameRect().pos.y, ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.width, compositeShape.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.height, compositeShape.getFrameRect().height, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_compoiste_shape_getting_center)
{
  stolyarov::Rectangle rectangle(0.7, 1.9, { 2.7, 3.1 });
  stolyarov::Circle circle(5.11, { 1.1, 2.1 });
  stolyarov::CompositeShape::shapePtr shape1 = std::make_shared<stolyarov::Rectangle>(rectangle);
  stolyarov::CompositeShape::shapePtr shape2 = std::make_shared<stolyarov::Circle>(circle);
  stolyarov::CompositeShape compositeShape;
  compositeShape.addElement(shape1);
  compositeShape.addElement(shape2);
  stolyarov::rectangle_t frameRect = compositeShape.getFrameRect();
  BOOST_CHECK_CLOSE(frameRect.pos.x, compositeShape.getCenter().x, ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.pos.y, compositeShape.getCenter().y, ACCURACY);
}
