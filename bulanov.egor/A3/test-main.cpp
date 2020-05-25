#define BOOST_TEST_MODULE mytest
#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <memory>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double PERMISSIBLE_ACCURACY = 0.00001;

BOOST_AUTO_TEST_CASE(test_invalid_index_compositeShape)
{
  bulanov::CompositeShape compositeShape;
  BOOST_CHECK_THROW(compositeShape[-1], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_index_compositeShape_deliting)
{
  bulanov::CompositeShape compositeShape;
  BOOST_CHECK_THROW(compositeShape.removeElement(2), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_index_compositeShape_adding)
{
  bulanov::CompositeShape compositeShape;
  bulanov::CompositeShape::shapePtr shape = nullptr;
  BOOST_CHECK_THROW(compositeShape.addElement(shape), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_rate_scaling_composteShape)
{
  bulanov::CompositeShape compositeShape(1);
  bulanov::Rectangle rectangle({ 0.4, 5.0 }, 3.1, 4.8 );
  bulanov::CompositeShape::shapePtr shape = std::make_shared<bulanov::Rectangle>(rectangle);
  compositeShape.addElement(shape);
  BOOST_CHECK_THROW(compositeShape.scale(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_radius_circle)
{
  BOOST_CHECK_THROW(bulanov::Circle circle(-0.2, {1.1, 2.1}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_rate_scaling_circle)
{
  bulanov::Circle circle(5.11, {1.1, 2.1});
  BOOST_CHECK_THROW(circle.scale(-5.2), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_width_rectangle)
{
  BOOST_CHECK_THROW(bulanov::Rectangle rectangle({3.2, 2.1}, -3, 7), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_height_rectangle)
{
  BOOST_CHECK_THROW(bulanov::Rectangle rectangle({3.2, 2.1}, 3, 0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_rate_scaling_rectangle)
{
  bulanov::Rectangle rectangle({3.2, 2.1}, 3, 7);
  BOOST_CHECK_THROW(rectangle.scale(-1.7), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_permanency_compositeShape_moving)
{
  bulanov::CompositeShape compositeShape(2);
  bulanov::Circle circle(5.11, {1.1, 2.1});
  bulanov::Rectangle rectangle({3.2, 2.1}, 3.0, 2.4);
  bulanov::CompositeShape::shapePtr shape1 = std::make_shared<bulanov::Circle>(circle);
  bulanov::CompositeShape::shapePtr shape2 = std::make_shared<bulanov::Rectangle>(rectangle);
  compositeShape.addElement(shape1);
  compositeShape.addElement(shape2);

  const double x1 = 1.8;
  const double y1 = 3.0;
  const double dx = 4.0;
  const double dy = 2.8;

  const double area = compositeShape.getArea();
  const double frameHeight = compositeShape.getFrameRect().height;
  const double frameWidth = compositeShape.getFrameRect().width;
  const double areaCircle = compositeShape[0]->getArea();
  const double areaRectangle = compositeShape[1]->getArea();

  compositeShape.move({x1, y1});
  compositeShape.move(dx, dy);
  BOOST_CHECK_CLOSE(compositeShape[0]->getFrameRect().pos.x, x1 + dx, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape[0]->getFrameRect().pos.y, y1 + dy, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape[1]->getFrameRect().pos.x, x1 + dx, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape[1]->getFrameRect().pos.y, y1 + dy, PERMISSIBLE_ACCURACY);

  compositeShape.move(13.1, 1.1);
  BOOST_CHECK_CLOSE(area, compositeShape.getArea(), PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameHeight, compositeShape.getFrameRect().height, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameWidth, compositeShape.getFrameRect().width, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(areaCircle, compositeShape[0]->getArea(), PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(areaRectangle, compositeShape[1]->getArea(), PERMISSIBLE_ACCURACY);

  compositeShape.move(bulanov::point_t{7.2, 4.1});
  BOOST_CHECK_CLOSE(area, compositeShape.getArea(), PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameHeight, compositeShape.getFrameRect().height, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameWidth, compositeShape.getFrameRect().width, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(areaCircle, compositeShape[0]->getArea(), PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(areaRectangle, compositeShape[1]->getArea(), PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_compositeShape_coping)
{
  bulanov::Circle circle(5, { 4.6, 7.0 });
  bulanov::CompositeShape::shapePtr shape1 = std::make_shared<bulanov::Circle>(circle);
  bulanov::Rectangle rectangle({3.2, 2.1}, 3.0, 2.4);
  bulanov::CompositeShape::shapePtr shape2 = std::make_shared<bulanov::Rectangle>(rectangle);

  bulanov::CompositeShape compositeShape1(2);
  compositeShape1.addElement(shape1);
  compositeShape1.addElement(shape2);
  bulanov::CompositeShape compositeShape2(compositeShape1);
  BOOST_CHECK_CLOSE(compositeShape1.getCenter().x, compositeShape2.getCenter().x, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape1.getCenter().y, compositeShape2.getCenter().y, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape1.getArea(), compositeShape2.getArea(), PERMISSIBLE_ACCURACY);

  bulanov::CompositeShape compositeShape3;
  compositeShape3 = compositeShape1;
  BOOST_CHECK_CLOSE(compositeShape3.getCenter().x, compositeShape1.getCenter().x, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape3.getCenter().y, compositeShape1.getCenter().y, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape3.getArea(), compositeShape1.getArea(), PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_valid_common_area)
{
  bulanov::Rectangle rectangle( { 2.7, 3.1 }, 0.7, 1.9);
  bulanov::Circle circle(5.11, {1.1, 2.1});
  bulanov::CompositeShape::shapePtr shape1 = std::make_shared<bulanov::Rectangle>(rectangle);
  bulanov::CompositeShape::shapePtr shape2 = std::make_shared<bulanov::Circle>(circle);
  bulanov::CompositeShape compositeShape(2);
  compositeShape.addElement(shape1);
  compositeShape.addElement(shape2);
  BOOST_CHECK_CLOSE(shape1->getArea() + shape2->getArea(), compositeShape.getArea(), PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_getting_frameRec_compositeShape)
{
  bulanov::Rectangle rectangle( { 3.0, 3.0 }, 2.0, 5.0);
  bulanov::Circle circle(1.0, {-1.0, 0.0});
  bulanov::CompositeShape::shapePtr shape1 = std::make_shared<bulanov::Rectangle>(rectangle);
  bulanov::CompositeShape::shapePtr shape2 = std::make_shared<bulanov::Circle>(circle);
  bulanov::CompositeShape compositeShape(2);
  compositeShape.addElement(shape1);
  compositeShape.addElement(shape2);
  bulanov::rectangle_t frameRect;
  frameRect.width = 6.0;
  frameRect.height = 6.5;
  frameRect.pos.x = 1.0;
  frameRect.pos.y = 2.25;
  BOOST_CHECK_CLOSE(frameRect.pos.x, compositeShape.getFrameRect().pos.x, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.pos.y, compositeShape.getFrameRect().pos.y, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.width, compositeShape.getFrameRect().width, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.height, compositeShape.getFrameRect().height, PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_getting_center_compositeShape)
{
  bulanov::Rectangle rectangle( { 2.7, 3.1 }, 0.7, 1.9);
  bulanov::Circle circle(5.11, {1.1, 2.1});
  bulanov::CompositeShape::shapePtr shape1 = std::make_shared<bulanov::Rectangle>(rectangle);
  bulanov::CompositeShape::shapePtr shape2 = std::make_shared<bulanov::Circle>(circle);
  bulanov::CompositeShape compositeShape(2);
  compositeShape.addElement(shape1);
  compositeShape.addElement(shape2);
  bulanov::rectangle_t frameRect = compositeShape.getFrameRect();
  BOOST_CHECK_CLOSE(frameRect.pos.x, compositeShape.getCenter().x, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.pos.y, compositeShape.getCenter().y, PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_permanency_circle_moving)
{
  bulanov::Circle circle(5.11, {1.1, 2.1});
  const bulanov::rectangle_t frameRect = circle.getFrameRect();
  const double area = circle.getArea();

  circle.move(11.2, 12.3);
  BOOST_CHECK_CLOSE(frameRect.width, circle.getFrameRect().width, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.height, circle.getFrameRect().height, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(area, circle.getArea(), PERMISSIBLE_ACCURACY);

  circle.move({-10.2, -9.3});
  BOOST_CHECK_CLOSE(frameRect.width, circle.getFrameRect().width, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.height, circle.getFrameRect().height, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(area, circle.getArea(), PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_circle_scaling_area)
{
  bulanov::Circle circle(5.11, {1.1, 2.1});
  const double area = circle.getArea();
  const double rate = 0.7;
  circle.scale(rate);
  BOOST_CHECK_CLOSE(area * rate * rate, circle.getArea(), PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_permanency_rectangle_moving)
{
  bulanov::Rectangle rectangle({3.2, 2.1}, 3, 7);
  bulanov::rectangle_t frameRect = rectangle.getFrameRect();
  const double area = rectangle.getArea();

  rectangle.move({2.2, 10.3});
  BOOST_CHECK_CLOSE(frameRect.width, rectangle.getFrameRect().width, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.height, rectangle.getFrameRect().height, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(area, rectangle.getArea(), PERMISSIBLE_ACCURACY);

  rectangle.move(-5.2, -3.3);
  BOOST_CHECK_CLOSE(frameRect.width, rectangle.getFrameRect().width, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.height, rectangle.getFrameRect().height, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(area, rectangle.getArea(), PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rectangle_scaling_area)
{
  bulanov::Rectangle rectangle({1.0, 1.0}, 10.0, 14.5);
  const double area = rectangle.getArea();
  const double rate = 3.1;
  rectangle.scale(rate);
  BOOST_CHECK_CLOSE(area * rate * rate, rectangle.getArea(), PERMISSIBLE_ACCURACY);
}







