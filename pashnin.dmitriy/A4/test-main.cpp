
#include <cassert>
#include <functional>
#include <vector>
#include <string>
#include <cmath>
#include "../common/matrix.hpp"
#include "../common/circle.hpp"
#include "../common/composite-shape.hpp"
#include "../common/rectangle.hpp"
#include "../common/triangle.hpp"
#include "../common/polygon.hpp"
#include "../common/specs.hpp"

using shapePtr = std::shared_ptr<pashnin::Shape>;

typedef void (*func)();

const double ACCURACY = 0.0001;
const double ROTATION_ANGLE = 15;

bool checkClose(double val1, double val2, double acc)
{
  return std::abs(val1 - val2) < acc;
}

void testCircleRotate()
{
  std::string testName = "Circle rotate test";
  pashnin::Circle circle(1, {1, 1});
  const double area = circle.getArea();
  const pashnin::rectangle_t frameRect = circle.getFrameRect();
  circle.rotate(ROTATION_ANGLE);
  
  assert(checkClose(circle.getArea(), area, ACCURACY));
  assert(checkClose(circle.getFrameRect().pos.x, frameRect.pos.x, ACCURACY));
  assert(checkClose(circle.getFrameRect().pos.y, frameRect.pos.y, ACCURACY));
}

void testRectangleRotate()
{
  std::string testName = "Rectangle rotate test";
  pashnin::Rectangle rectangle(2, 3, {1, 1});
  const double area = rectangle.getArea();
  const pashnin::rectangle_t frameRect = rectangle.getFrameRect();
  rectangle.rotate(ROTATION_ANGLE);
  
  assert(checkClose(rectangle.getArea(), area, ACCURACY));
  assert(checkClose(rectangle.getFrameRect().pos.x, frameRect.pos.x, ACCURACY));
  assert(checkClose(rectangle.getFrameRect().pos.y, frameRect.pos.y, ACCURACY));
  assert(checkClose(
    rectangle.getFrameRect().width,
    frameRect.width * fabs(cos(specs::toRadians(ROTATION_ANGLE))) +
    frameRect.height * fabs(sin(specs::toRadians(ROTATION_ANGLE))), ACCURACY));
  assert(checkClose(
    rectangle.getFrameRect().height,
    frameRect.width * fabs(sin(specs::toRadians(ROTATION_ANGLE))) +
    frameRect.height * fabs(cos(specs::toRadians(ROTATION_ANGLE))), ACCURACY));
}

void testTriangleRotate()
{
  pashnin::Triangle triangle({2, 2}, {1, 0}, {5, 3});
  const double area = triangle.getArea();
  pashnin::point_t point_one = triangle.getTop1();
  pashnin::point_t point_two = triangle.getTop2();
  pashnin::point_t point_three = triangle.getTop3();
  triangle.rotate(ROTATION_ANGLE);
  assert(checkClose(triangle.getArea(), area, ACCURACY));
  assert(checkClose(
    triangle.getTop1().x,
    (point_one.x - triangle.getCenterX()) *
    cos(specs::toRadians(ROTATION_ANGLE)) -
    (point_one.y - triangle.getCenterY()) *
    sin(specs::toRadians(ROTATION_ANGLE)) +
    triangle.getCenterX(), ACCURACY));
  assert(checkClose(
    triangle.getTop1().y,
    (point_one.x - triangle.getCenterX()) *
    sin(specs::toRadians(ROTATION_ANGLE)) +
    (point_one.y - triangle.getCenterY()) *
    cos(specs::toRadians(ROTATION_ANGLE)) +
    triangle.getCenterY(), ACCURACY));
  assert(checkClose(
    triangle.getTop2().x,
    (point_two.x - triangle.getCenterX()) *
    cos(specs::toRadians(ROTATION_ANGLE)) -
    (point_two.y - triangle.getCenterY()) *
    sin(specs::toRadians(ROTATION_ANGLE)) +
    triangle.getCenterX(), ACCURACY));
  assert(checkClose(
    triangle.getTop2().y,
    (point_two.x - triangle.getCenterX()) *
    sin(specs::toRadians(ROTATION_ANGLE)) +
    (point_two.y - triangle.getCenterY()) *
    cos(specs::toRadians(ROTATION_ANGLE)) +
    triangle.getCenterY(), ACCURACY));
  assert(checkClose(
    triangle.getTop3().x,
    (point_three.x - triangle.getCenterX()) *
    cos(specs::toRadians(ROTATION_ANGLE)) -
    (point_three.y - triangle.getCenterY()) *
    sin(specs::toRadians(ROTATION_ANGLE)) +
    triangle.getCenterX(), ACCURACY));
  assert(checkClose(
    triangle.getTop3().y,
    (point_three.x - triangle.getCenterX()) *
    sin(specs::toRadians(ROTATION_ANGLE)) +
    (point_three.y - triangle.getCenterY()) *
    cos(specs::toRadians(ROTATION_ANGLE)) +
    triangle.getCenterY(), ACCURACY));
}

void testPolygonRotate()
{
  pashnin::Polygon polygon({{0, 0}, {0, 3}, {4, 0}});
  const double area = polygon.getArea();
  pashnin::point_t pos = polygon.getPosition();
  const double width = polygon.getFrameRect().width;
  const double height = polygon.getFrameRect().height;
  polygon.rotate(90);
  assert(checkClose(polygon.getArea(), area, ACCURACY));
  assert(checkClose(polygon.getPosition().x, pos.x, ACCURACY));
  assert(checkClose(polygon.getPosition().y, pos.y, ACCURACY));
  assert(checkClose(polygon.getFrameRect().width, height, ACCURACY));
  assert(checkClose(polygon.getFrameRect().height, width, ACCURACY));
}

void testCompositeShapeRotate()
{
  std::string testName = "Composite shape rotate test";
  pashnin::Rectangle rectangle(8, 8, {5, 5});
  pashnin::CompositeShape compositeShape(2);
  shapePtr shape1 = std::make_shared<pashnin::Rectangle>(rectangle);
  compositeShape.addShape(shape1);
  pashnin::Circle circle(5, {5, 5});
  shapePtr shape2 = std::make_shared<pashnin::Circle>(circle);
  compositeShape.addShape(shape2);
  const double area = compositeShape.getArea();
  const pashnin::rectangle_t frameRect = compositeShape.getFrameRect();
  compositeShape.rotate(ROTATION_ANGLE);
  assert(checkClose(compositeShape.getArea(), area, ACCURACY));
  assert(checkClose(compositeShape.getFrameRect().pos.x, frameRect.pos.x, ACCURACY));
  assert(checkClose(compositeShape.getFrameRect().pos.y, frameRect.pos.y, ACCURACY));
  assert(checkClose(compositeShape.getFrameRect().width, frameRect.width, ACCURACY));
  assert(checkClose(compositeShape.getFrameRect().height, frameRect.height, ACCURACY));
}

void testPolygonScale()
{
  pashnin::Polygon polygon({{0, 0}, {0, 1}, {1, 0}});
  const double area = polygon.getArea();
  polygon.scale(2);
  assert(checkClose(polygon.getArea(), area * 4, ACCURACY));
}

void testMatrixAddShape()
{
  std::string testName = "Matrix add shape test";
  pashnin::Rectangle rectangle(8, 8, {5, 5});
  pashnin::Matrix matrix;
  shapePtr shape1 = std::make_shared<pashnin::Rectangle>(rectangle);
  matrix.addShape(shape1);
  pashnin::Circle circle(5, {5, 5});
  shapePtr shape2 = std::make_shared<pashnin::Circle>(circle);
  matrix.addShape(shape2);
  assert(matrix.getShape(0, 0) == shape1);
  assert(matrix.getShape(1, 0) == shape2);
}

void testCompositeShapeToMatrix()
{
  std::string testName = "Composite shape to matrix test";
  pashnin::Rectangle rectangle(8, 8, {5, 5});
  pashnin::CompositeShape compositeShape(2);
  shapePtr shape1 = std::make_shared<pashnin::Rectangle>(rectangle);
  compositeShape.addShape(shape1);
  pashnin::Circle circle(5, {5, 5});
  shapePtr shape2 = std::make_shared<pashnin::Circle>(circle);
  compositeShape.addShape(shape2);
  pashnin::Matrix matrix = compositeShape.toMatrix();
  assert(matrix.getShape(0, 0) == shape1);
  assert(matrix.getShape(1, 0) == shape2);
}

template<class T>
bool checkException(func f)
{
  try
  {
    f();
  }
  catch (T &e)
  {
    return true;
  }
  catch (std::exception &e)
  {
  }
  return false;
}

void testMatrixInvalidShapeToAdd()
{
  std::string testName = "Matrix invalid shape to add test";
  assert(checkException<std::invalid_argument>([]()
  {
    pashnin::Matrix matrix;
    matrix.addShape(nullptr);
  }));
}

void testMatrixShapeInvalidIndex()
{
  std::string testName = "Matrix invalid shape index test";
  assert(checkException<std::out_of_range>([]()
  {
    pashnin::Rectangle rectangle(8, 8, {5, 5});
    pashnin::Matrix matrix;
    shapePtr shape1 = std::make_shared<pashnin::Rectangle>(rectangle);
    matrix.addShape(shape1);
    matrix.getShape(1, 0);
  }));
  assert(checkException<std::out_of_range>([]()
  {
    pashnin::Rectangle rectangle(8, 8, {5, 5});
    pashnin::Matrix matrix;
    shapePtr shape1 = std::make_shared<pashnin::Rectangle>(rectangle);
    matrix.addShape(shape1);
    matrix.getShape(0, 1);
  }));
}

void testPolygonConstructorInvalidArgument()
{
  assert(checkException<std::invalid_argument>([]()
  {
    pashnin::Polygon({{{0, 0}, {10, 1}}});
  }));
  assert(checkException<std::invalid_argument>([]()
  {
    pashnin::Polygon({{0, 0}, {0, 0}, {0, 1}});
  }));
  assert(checkException<std::invalid_argument>([]()
  {
    pashnin::Polygon({{0, 0}, {0, 3}, {1, 1}, {3, 0}});
  }));
}

void testPolygonScaleInvalidArgument()
{
  assert(checkException<std::invalid_argument>([]()
  {
    pashnin::Polygon polygon({{0, 0}, {0, 3}, {4, 0}});
    polygon.scale(-1);
  }));
}

int main()
{
  std::vector<std::function<void()>> tests =
    {
      testCircleRotate,
      testRectangleRotate,
      testTriangleRotate,
      testPolygonRotate,
      testCompositeShapeRotate,
      testPolygonScale,
      testMatrixAddShape,
      testCompositeShapeToMatrix,
      testMatrixInvalidShapeToAdd,
      testMatrixShapeInvalidIndex,
      testPolygonConstructorInvalidArgument,
      testPolygonScaleInvalidArgument
    };
  for (std::function<void()> &test : tests)
  {
    test();
  }
  return 0;
}
