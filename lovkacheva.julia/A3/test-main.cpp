#define BOOST_TEST_MODULE A3 Test

#include <memory>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

const double TOLERANCE = 0.000001;

BOOST_AUTO_TEST_CASE(test_composite_shape_scale_invalid_coefficient)
{
  lovkacheva::CompositeShape compositeShape;
  BOOST_CHECK_THROW(compositeShape.scale(-3.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_scale)
{
  std::shared_ptr<lovkacheva::Circle> circle = std::make_shared<lovkacheva::Circle>(5, lovkacheva::point_t{1, 10});
  std::shared_ptr<lovkacheva::Rectangle> rectangle
      = std::make_shared<lovkacheva::Rectangle>(lovkacheva::rectangle_t{10, 10, {1, -10}});
  lovkacheva::CompositeShape compositeShape(2);
  compositeShape.addShape(rectangle);
  compositeShape.addShape(circle);
  lovkacheva::point_t compositeShapePosition = compositeShape.getFrameRect().pos;
  const double COEFFICIENTS[] = {2.5, 0.33};
  for (double COEFFICIENT : COEFFICIENTS)
  {
    double formerRectangleArea = rectangle->getArea();
    double formerCircleArea = circle->getArea();
    double formerCompositeShapeArea = compositeShape.getArea();
    double formerRectangleDistanceFromCentreX = rectangle->getFrameRect().pos.x - compositeShapePosition.x;
    double formerRectangleDistanceFromCentreY = rectangle->getFrameRect().pos.y - compositeShapePosition.y;
    double formerCircleDistanceFromCentreX = circle->getFrameRect().pos.x - compositeShapePosition.x;
    double formerCircleDistanceFromCentreY = circle->getFrameRect().pos.y - compositeShapePosition.y;
    compositeShape.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(formerCompositeShapeArea * COEFFICIENT * COEFFICIENT, compositeShape.getArea(), TOLERANCE);
    BOOST_CHECK_CLOSE(formerRectangleArea * COEFFICIENT * COEFFICIENT, rectangle->getArea(), TOLERANCE);
    BOOST_CHECK_CLOSE(formerCircleArea * COEFFICIENT * COEFFICIENT, circle->getArea(), TOLERANCE);
    BOOST_CHECK_CLOSE(formerRectangleDistanceFromCentreX * COEFFICIENT,
        rectangle->getFrameRect().pos.x - compositeShapePosition.x, TOLERANCE);
    BOOST_CHECK_CLOSE(formerRectangleDistanceFromCentreY * COEFFICIENT,
        rectangle->getFrameRect().pos.y - compositeShapePosition.y, TOLERANCE);
    BOOST_CHECK_CLOSE(formerCircleDistanceFromCentreX * COEFFICIENT,
        circle->getFrameRect().pos.x - compositeShapePosition.x, TOLERANCE);
    BOOST_CHECK_CLOSE(formerCircleDistanceFromCentreY * COEFFICIENT,
        circle->getFrameRect().pos.y - compositeShapePosition.y, TOLERANCE);
  }
}

BOOST_AUTO_TEST_CASE(test_composite_shape_move)
{
  std::shared_ptr<lovkacheva::Circle> circle = std::make_shared<lovkacheva::Circle>(5, lovkacheva::point_t{1, 10});
  std::shared_ptr<lovkacheva::Rectangle> rectangle
      = std::make_shared<lovkacheva::Rectangle>(lovkacheva::rectangle_t{10, 10, {1, -10}});
  lovkacheva::CompositeShape compositeShape(2);
  compositeShape.addShape(rectangle);
  compositeShape.addShape(circle);
  lovkacheva::rectangle_t formerRectangleFrameRect = rectangle->getFrameRect();
  lovkacheva::rectangle_t formerCircleFrameRect = circle->getFrameRect();
  lovkacheva::rectangle_t formerCompositeShapeFrameRect = compositeShape.getFrameRect();
  const double dx = 1.0;
  const double dy = 2.0;
  compositeShape.move(dx, dy);
  BOOST_CHECK_CLOSE(formerCompositeShapeFrameRect.pos.x + dx, compositeShape.getFrameRect().pos.x, TOLERANCE);
  BOOST_CHECK_CLOSE(formerCompositeShapeFrameRect.pos.y + dy, compositeShape.getFrameRect().pos.y, TOLERANCE);
  BOOST_CHECK_CLOSE(formerRectangleFrameRect.pos.x + dx, rectangle->getFrameRect().pos.x, TOLERANCE);
  BOOST_CHECK_CLOSE(formerRectangleFrameRect.pos.y + dy, rectangle->getFrameRect().pos.y, TOLERANCE);
  BOOST_CHECK_CLOSE(formerCircleFrameRect.pos.x + dx, circle->getFrameRect().pos.x, TOLERANCE);
  BOOST_CHECK_CLOSE(formerCircleFrameRect.pos.y + dy, circle->getFrameRect().pos.y, TOLERANCE);
  const lovkacheva::point_t newPosition = {-1.8, 2.78};
  compositeShape.move(newPosition);
  lovkacheva::point_t newRectanglePosition{newPosition.x + formerRectangleFrameRect.pos.x
      - formerCompositeShapeFrameRect.pos.x, newPosition.y + formerRectangleFrameRect.pos.y
      - formerCompositeShapeFrameRect.pos.y};
  lovkacheva::point_t newCirclePosition{newPosition.x + formerCircleFrameRect.pos.x
      - formerCompositeShapeFrameRect.pos.x, newPosition.y + formerCircleFrameRect.pos.y
      - formerCompositeShapeFrameRect.pos.y};
  BOOST_CHECK_CLOSE(newPosition.x, compositeShape.getFrameRect().pos.x, TOLERANCE);
  BOOST_CHECK_CLOSE(newPosition.y, compositeShape.getFrameRect().pos.y, TOLERANCE);
  BOOST_CHECK_CLOSE(newRectanglePosition.x, rectangle->getFrameRect().pos.x, TOLERANCE);
  BOOST_CHECK_CLOSE(newRectanglePosition.y, rectangle->getFrameRect().pos.y, TOLERANCE);
  BOOST_CHECK_CLOSE(newCirclePosition.x, circle->getFrameRect().pos.x, TOLERANCE);
  BOOST_CHECK_CLOSE(newCirclePosition.y, circle->getFrameRect().pos.y, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_get_frame_rect)
{
  lovkacheva::CompositeShape compositeShape(4);
  compositeShape.addShape(std::make_shared<lovkacheva::Rectangle>(lovkacheva::rectangle_t{10, 10, {5, 1}}));
  compositeShape.addShape(std::make_shared<lovkacheva::Circle>(10, lovkacheva::point_t{-5, 1}));
  compositeShape.addShape(std::make_shared<lovkacheva::Rectangle>(lovkacheva::rectangle_t{10, 10, {1, -10}}));
  compositeShape.addShape(std::make_shared<lovkacheva::Circle>(5, lovkacheva::point_t{1, 10}));
  lovkacheva::rectangle_t frameRect = compositeShape.getFrameRect();
  BOOST_CHECK_CLOSE(frameRect.width, 25.0, TOLERANCE);
  BOOST_CHECK_CLOSE(frameRect.height, 30.0, TOLERANCE);
  BOOST_CHECK_CLOSE(frameRect.pos.x, -2.5, TOLERANCE);
  BOOST_CHECK_CLOSE(frameRect.pos.y, 0, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_index_operator_out_of_range)
{
  lovkacheva::CompositeShape compositeShape;
  BOOST_CHECK_THROW(compositeShape[0], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_get_area)
{
  std::shared_ptr<lovkacheva::Circle> circle = std::make_shared<lovkacheva::Circle>(5, lovkacheva::point_t{1, 10});
  std::shared_ptr<lovkacheva::Rectangle> rectangle
      = std::make_shared<lovkacheva::Rectangle>(lovkacheva::rectangle_t{10, 10, {1, -10}});
  lovkacheva::CompositeShape compositeShape(2);
  compositeShape.addShape(circle);
  compositeShape.addShape(rectangle);
  BOOST_CHECK_CLOSE(circle->getArea() + rectangle->getArea(), compositeShape.getArea(), TOLERANCE);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_add_shape)
{
  std::shared_ptr<lovkacheva::Circle> circle = std::make_shared<lovkacheva::Circle>(5, lovkacheva::point_t{1, 10});
  lovkacheva::CompositeShape compositeShape(1);
  BOOST_CHECK(compositeShape.getSize() == 0);
  compositeShape.addShape(circle);
  BOOST_CHECK(compositeShape[0] == circle);
  BOOST_CHECK(compositeShape.getSize() == 1);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_add_shape_nullptr)
{
  lovkacheva::CompositeShape compositeShape;
  BOOST_CHECK_THROW(compositeShape.addShape(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_remove_shape)
{
  std::shared_ptr<lovkacheva::Circle> circle = std::make_shared<lovkacheva::Circle>(5, lovkacheva::point_t{1, 10});
  lovkacheva::CompositeShape compositeShape(1);
  compositeShape.addShape(circle);
  BOOST_CHECK(compositeShape.getSize() == 1);
  compositeShape.removeShape(0);
  BOOST_CHECK(compositeShape.getSize() == 0);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_remove_shape_out_of_range)
{
  lovkacheva::CompositeShape compositeShape;
  BOOST_CHECK_THROW(compositeShape.removeShape(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_get_size)
{
  std::shared_ptr<lovkacheva::Circle> circle = std::make_shared<lovkacheva::Circle>(5, lovkacheva::point_t{1, 10});
  std::shared_ptr<lovkacheva::Rectangle> rectangle
      = std::make_shared<lovkacheva::Rectangle>(lovkacheva::rectangle_t{10, 10, {1, -10}});
  lovkacheva::CompositeShape compositeShape(2);
  compositeShape.addShape(circle);
  compositeShape.addShape(rectangle);
  BOOST_CHECK(compositeShape.getSize() == 2);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_copy_constructor)
{
  std::shared_ptr<lovkacheva::Circle> circle = std::make_shared<lovkacheva::Circle>(5, lovkacheva::point_t{1, 10});
  std::shared_ptr<lovkacheva::Rectangle> rectangle
      = std::make_shared<lovkacheva::Rectangle>(lovkacheva::rectangle_t{10, 10, {1, -10}});
  lovkacheva::CompositeShape compositeShape1(2);
  compositeShape1.addShape(circle);
  compositeShape1.addShape(rectangle);
  lovkacheva::CompositeShape compositeShape2(compositeShape1);
  BOOST_CHECK(compositeShape1[0] == compositeShape2[0]);
  BOOST_CHECK(compositeShape1[1] == compositeShape2[1]);
  BOOST_CHECK_CLOSE(compositeShape1.getFrameRect().pos.x, compositeShape2.getFrameRect().pos.x, TOLERANCE);
  BOOST_CHECK_CLOSE(compositeShape1.getFrameRect().pos.y, compositeShape2.getFrameRect().pos.y, TOLERANCE);
  BOOST_CHECK_CLOSE(compositeShape1.getFrameRect().width, compositeShape2.getFrameRect().width, TOLERANCE);
  BOOST_CHECK_CLOSE(compositeShape1.getFrameRect().height, compositeShape2.getFrameRect().height, TOLERANCE);
  BOOST_CHECK_CLOSE(compositeShape1.getArea(), compositeShape2.getArea(), TOLERANCE);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_assignment_operator)
{
  std::shared_ptr<lovkacheva::Circle> circle = std::make_shared<lovkacheva::Circle>(5, lovkacheva::point_t{1, 10});
  std::shared_ptr<lovkacheva::Rectangle> rectangle
      = std::make_shared<lovkacheva::Rectangle>(lovkacheva::rectangle_t{10, 10, {1, -10}});
  lovkacheva::CompositeShape compositeShape1(2);
  compositeShape1.addShape(circle);
  compositeShape1.addShape(rectangle);
  lovkacheva::CompositeShape compositeShape2;
  compositeShape2 = compositeShape1;
  BOOST_CHECK(compositeShape1[0] == compositeShape2[0]);
  BOOST_CHECK(compositeShape1[1] == compositeShape2[1]);
  BOOST_CHECK_CLOSE(compositeShape1.getFrameRect().pos.x, compositeShape2.getFrameRect().pos.x, TOLERANCE);
  BOOST_CHECK_CLOSE(compositeShape1.getFrameRect().pos.y, compositeShape2.getFrameRect().pos.y, TOLERANCE);
  BOOST_CHECK_CLOSE(compositeShape1.getFrameRect().width, compositeShape2.getFrameRect().width, TOLERANCE);
  BOOST_CHECK_CLOSE(compositeShape1.getFrameRect().height, compositeShape2.getFrameRect().height, TOLERANCE);
  BOOST_CHECK_CLOSE(compositeShape1.getArea(), compositeShape2.getArea(), TOLERANCE);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_move_constructor)
{
  std::shared_ptr<lovkacheva::Circle> circle = std::make_shared<lovkacheva::Circle>(5, lovkacheva::point_t{1, 10});
  std::shared_ptr<lovkacheva::Rectangle> rectangle
      = std::make_shared<lovkacheva::Rectangle>(lovkacheva::rectangle_t{10, 10, {1, -10}});
  lovkacheva::CompositeShape compositeShape1(2);
  compositeShape1.addShape(circle);
  compositeShape1.addShape(rectangle);
  double positionX = compositeShape1.getFrameRect().pos.x;
  double positionY = compositeShape1.getFrameRect().pos.y;
  double frameRectWidth = compositeShape1.getFrameRect().width;
  double frameRectHeight = compositeShape1.getFrameRect().height;
  double area = compositeShape1.getArea();
  lovkacheva::CompositeShape compositeShape2(std::move(compositeShape1));
  BOOST_CHECK(circle == compositeShape2[0]);
  BOOST_CHECK(rectangle == compositeShape2[1]);
  BOOST_CHECK_CLOSE(positionX, compositeShape2.getFrameRect().pos.x, TOLERANCE);
  BOOST_CHECK_CLOSE(positionY, compositeShape2.getFrameRect().pos.y, TOLERANCE);
  BOOST_CHECK_CLOSE(frameRectWidth, compositeShape2.getFrameRect().width, TOLERANCE);
  BOOST_CHECK_CLOSE(frameRectHeight, compositeShape2.getFrameRect().height, TOLERANCE);
  BOOST_CHECK_CLOSE(area, compositeShape2.getArea(), TOLERANCE);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_move_assignment_operator)
{
  std::shared_ptr<lovkacheva::Circle> circle = std::make_shared<lovkacheva::Circle>(5, lovkacheva::point_t{1, 10});
  std::shared_ptr<lovkacheva::Rectangle> rectangle
      = std::make_shared<lovkacheva::Rectangle>(lovkacheva::rectangle_t{10, 10, {1, -10}});
  lovkacheva::CompositeShape compositeShape1(2);
  compositeShape1.addShape(circle);
  compositeShape1.addShape(rectangle);
  double positionX = compositeShape1.getFrameRect().pos.x;
  double positionY = compositeShape1.getFrameRect().pos.y;
  double frameRectWidth = compositeShape1.getFrameRect().width;
  double frameRectHeight = compositeShape1.getFrameRect().height;
  double area = compositeShape1.getArea();
  lovkacheva::CompositeShape compositeShape2;
  compositeShape2 = std::move(compositeShape1);
  BOOST_CHECK(circle == compositeShape2[0]);
  BOOST_CHECK(rectangle == compositeShape2[1]);
  BOOST_CHECK_CLOSE(positionX, compositeShape2.getFrameRect().pos.x, TOLERANCE);
  BOOST_CHECK_CLOSE(positionY, compositeShape2.getFrameRect().pos.y, TOLERANCE);
  BOOST_CHECK_CLOSE(frameRectWidth, compositeShape2.getFrameRect().width, TOLERANCE);
  BOOST_CHECK_CLOSE(frameRectHeight, compositeShape2.getFrameRect().height, TOLERANCE);
  BOOST_CHECK_CLOSE(area, compositeShape2.getArea(), TOLERANCE);
}
