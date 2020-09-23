#define BOOST_TEST_MODULE A4 Test

#include <memory>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "matrix.hpp"

const double TOLERANCE = 0.000001;

BOOST_AUTO_TEST_CASE(test_circle_rotate)
{
  lovkacheva::Circle circle(30, {1,2});
  double formerWidth = circle.getFrameRect().width;
  double formerHeight = circle.getFrameRect().height;
  double formerPosX = circle.getFrameRect().pos.x;
  double formerPosY = circle.getFrameRect().pos.y;
  circle.rotate(234);
  BOOST_CHECK_CLOSE(formerWidth, circle.getFrameRect().width, TOLERANCE);
  BOOST_CHECK_CLOSE(formerHeight, circle.getFrameRect().height, TOLERANCE);
  BOOST_CHECK_CLOSE(formerPosX, circle.getFrameRect().pos.x, TOLERANCE);
  BOOST_CHECK_CLOSE(formerPosY, circle.getFrameRect().pos.y, TOLERANCE);
}


BOOST_AUTO_TEST_CASE(test_rectangle_rotate)
{
  lovkacheva::Rectangle rectangle(lovkacheva::rectangle_t{20, 10, {1,1}});
  double expectedWidth = rectangle.getFrameRect().height;
  double expectedHeight = rectangle.getFrameRect().width;
  double formerPosX = rectangle.getFrameRect().pos.x;
  double formerPosY = rectangle.getFrameRect().pos.y;
  rectangle.rotate(-270);
  BOOST_CHECK_CLOSE(expectedWidth, rectangle.getFrameRect().width, TOLERANCE);
  BOOST_CHECK_CLOSE(expectedHeight, rectangle.getFrameRect().height, TOLERANCE);
  BOOST_CHECK_CLOSE(formerPosX, rectangle.getFrameRect().pos.x, TOLERANCE);
  BOOST_CHECK_CLOSE(formerPosY, rectangle.getFrameRect().pos.y, TOLERANCE);

}

BOOST_AUTO_TEST_CASE(test_composite_shape_rotate)
{
  std::shared_ptr<lovkacheva::Rectangle> rectangle
      = std::make_shared<lovkacheva::Rectangle>(lovkacheva::rectangle_t{40, 40, {-40, -40}});
  std::shared_ptr<lovkacheva::Circle> circle
      = std::make_shared<lovkacheva::Circle>(5, lovkacheva::point_t{15, 15});
  lovkacheva::CompositeShape compositeShape;
  compositeShape.addShape(rectangle);
  compositeShape.addShape(circle);
  double expectedWidth = compositeShape.getFrameRect().height;
  double expectedHeight = compositeShape.getFrameRect().width;
  double formerPosX = compositeShape.getFrameRect().pos.x;
  double formerPosY = compositeShape.getFrameRect().pos.y;
  compositeShape.rotate(90);
  BOOST_CHECK_CLOSE(expectedWidth, compositeShape.getFrameRect().width, TOLERANCE);
  BOOST_CHECK_CLOSE(expectedHeight, compositeShape.getFrameRect().height, TOLERANCE);
  BOOST_CHECK_CLOSE(formerPosX, compositeShape.getFrameRect().pos.x, TOLERANCE);
  BOOST_CHECK_CLOSE(formerPosY, compositeShape.getFrameRect().pos.y, TOLERANCE);
  BOOST_CHECK_CLOSE(circle->getFrameRect().pos.x, -55.0, TOLERANCE);
  BOOST_CHECK_CLOSE(circle->getFrameRect().pos.y, 15.0, TOLERANCE);
  BOOST_CHECK_CLOSE(rectangle->getFrameRect().pos.x, 0.0, TOLERANCE);
  BOOST_CHECK_CLOSE(rectangle->getFrameRect().pos.y, -40.0, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(test_matrix_layering)
{
  std::shared_ptr<lovkacheva::Rectangle> rectangle1
      = std::make_shared<lovkacheva::Rectangle>(lovkacheva::rectangle_t{40, 40, {-40, -40}});
  std::shared_ptr<lovkacheva::Circle> circle1
      = std::make_shared<lovkacheva::Circle>(5, lovkacheva::point_t{15, 15});
  std::shared_ptr<lovkacheva::CompositeShape> compositeShape = std::make_shared<lovkacheva::CompositeShape> ();
  compositeShape->addShape(rectangle1);
  compositeShape->addShape(circle1);
  std::shared_ptr<lovkacheva::Rectangle> rectangle2
      = std::make_shared<lovkacheva::Rectangle>(lovkacheva::rectangle_t{40, 20, {30, -40}});
  std::shared_ptr<lovkacheva::Circle> circle2
      = std::make_shared<lovkacheva::Circle>(20, lovkacheva::point_t{60, -20});
  lovkacheva::Matrix matrix;
  matrix.addShape(compositeShape);
  matrix.addShape(circle2);
  matrix.addShape(rectangle2);
  matrix.addShape(rectangle1);
  matrix.addShape(circle1);
  matrix.addShape(circle2);
  BOOST_CHECK(matrix.getLayerSize(0) == 2);
  BOOST_CHECK(matrix.getLayerSize(1) == 3);
  BOOST_CHECK(matrix.getLayerSize(2) == 1);
  BOOST_CHECK(matrix.getRows() == 3);
  BOOST_CHECK(matrix.getColumns() == 3);
  BOOST_CHECK(matrix[0][0] == compositeShape);
  BOOST_CHECK(matrix[0][1] == circle2);
  BOOST_CHECK(matrix[1][0] == rectangle2);
  BOOST_CHECK(matrix[1][1] == rectangle1);
  BOOST_CHECK(matrix[1][2] == circle1);
  BOOST_CHECK(matrix[2][0] == circle2);
}

BOOST_AUTO_TEST_CASE(test_matrix_out_of_range_exceptions)
{
  std::shared_ptr<lovkacheva::Rectangle> rectangle1
    = std::make_shared<lovkacheva::Rectangle>(lovkacheva::rectangle_t{40, 40, {-40, -40}});
  std::shared_ptr<lovkacheva::Circle> circle1
    = std::make_shared<lovkacheva::Circle>(5, lovkacheva::point_t{15, 15});
  std::shared_ptr<lovkacheva::CompositeShape> compositeShape = std::make_shared<lovkacheva::CompositeShape> ();
  compositeShape->addShape(rectangle1);
  compositeShape->addShape(circle1);
  std::shared_ptr<lovkacheva::Rectangle> rectangle2
    = std::make_shared<lovkacheva::Rectangle>(lovkacheva::rectangle_t{40, 20, {30, -40}});
  std::shared_ptr<lovkacheva::Circle> circle2
    = std::make_shared<lovkacheva::Circle>(20, lovkacheva::point_t{60, -20});
  lovkacheva::Matrix matrix;
  matrix.addShape(compositeShape);
  matrix.addShape(circle2);
  matrix.addShape(rectangle2);
  matrix.addShape(rectangle1);
  matrix.addShape(circle1);
  matrix.addShape(circle2);
  BOOST_CHECK_THROW(matrix[3][0],std::out_of_range);
  BOOST_CHECK_THROW(matrix[0][2],std::out_of_range);
  BOOST_CHECK_THROW(matrix[1][3],std::out_of_range);
  BOOST_CHECK_THROW(matrix[2][1],std::out_of_range);
  BOOST_CHECK_THROW(matrix.getLayerSize(3),std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_matrix_add_shape_nullptr_exception)
{
  lovkacheva::Matrix matrix;
  BOOST_CHECK_THROW(matrix.addShape(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_split)
{
  std::shared_ptr<lovkacheva::Rectangle> rectangleComponent1
    = std::make_shared<lovkacheva::Rectangle>(lovkacheva::rectangle_t{40, 40, {-40, -40}});
  std::shared_ptr<lovkacheva::Circle> circleComponent1
    = std::make_shared<lovkacheva::Circle>(5, lovkacheva::point_t{15, 15});
  std::shared_ptr<lovkacheva::CompositeShape> compositeShapeComponent = std::make_shared<lovkacheva::CompositeShape> ();
  compositeShapeComponent->addShape(rectangleComponent1);
  compositeShapeComponent->addShape(circleComponent1);
  std::shared_ptr<lovkacheva::Rectangle> rectangleComponent2
    = std::make_shared<lovkacheva::Rectangle>(lovkacheva::rectangle_t{40, 20, {30, -40}});
  std::shared_ptr<lovkacheva::Circle> circleComponent2
    = std::make_shared<lovkacheva::Circle>(20, lovkacheva::point_t{60, -20});
  lovkacheva::CompositeShape compositeShape;
  compositeShape.addShape(compositeShapeComponent);
  compositeShape.addShape(circleComponent2);
  compositeShape.addShape(rectangleComponent2);
  compositeShape.addShape(rectangleComponent1);
  compositeShape.addShape(circleComponent1);
  compositeShape.addShape(circleComponent2);
  lovkacheva::Matrix splitResult = compositeShape.split();
  BOOST_CHECK(splitResult.getLayerSize(0) == 2);
  BOOST_CHECK(splitResult.getLayerSize(1) == 3);
  BOOST_CHECK(splitResult.getLayerSize(2) == 1);
  BOOST_CHECK(splitResult.getRows() == 3);
  BOOST_CHECK(splitResult.getColumns() == 3);
  BOOST_CHECK(splitResult[0][0] == compositeShapeComponent);
  BOOST_CHECK(splitResult[0][1] == circleComponent2);
  BOOST_CHECK(splitResult[1][0] == rectangleComponent2);
  BOOST_CHECK(splitResult[1][1] == rectangleComponent1);
  BOOST_CHECK(splitResult[1][2] == circleComponent1);
  BOOST_CHECK(splitResult[2][0] == circleComponent2);
}
