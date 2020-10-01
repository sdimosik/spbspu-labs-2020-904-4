#include <cmath>
#include <cassert>
#include <vector>
#include <functional>
#include "matrix.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "optional.hpp"
#include "triangle.hpp"
#include "base-types.hpp"
#include "polygon.hpp"

typedef void (*func)();

const double ACCURACY = 0.001;
const double ROTATION_ANGLE = 15;

bool checkClose(double val1, double val2, double acc)
{
  return std::abs(val1 - val2) < acc;
}

void testCircleRotate()
{
  vorotnikov::Circle circle({4, {2, 0}});
  const double area = circle.getArea();
  const vorotnikov::rectangle_t frameRect = circle.getFrameRect();
  circle.rotate(ROTATION_ANGLE);
  assert(checkClose(circle.getArea(), area, ACCURACY));
  assert(checkClose(circle.getFrameRect().pos.x, frameRect.pos.x, ACCURACY));
  assert(checkClose(circle.getFrameRect().pos.y, frameRect.pos.y, ACCURACY));
}

void testRectangleRotate()
{
  vorotnikov::Rectangle rectangle(2, 4, {2, 2});
  const double area = rectangle.getArea();
  const vorotnikov::rectangle_t frameRect = rectangle.getFrameRect();
  rectangle.rotate(ROTATION_ANGLE);
  assert(checkClose(rectangle.getArea(), area, ACCURACY));
  assert(checkClose(rectangle.getFrameRect().pos.x, frameRect.pos.x, ACCURACY));
  assert(checkClose(rectangle.getFrameRect().pos.y, frameRect.pos.y, ACCURACY));
  assert(checkClose(rectangle.getFrameRect().width,
      fabs(frameRect.width * cos(optional::performToRadians(ROTATION_ANGLE)) +
        frameRect.height * sin(optional::performToRadians(ROTATION_ANGLE))), ACCURACY));
  assert(checkClose(rectangle.getFrameRect().height,
      fabs(frameRect.width * sin(optional::performToRadians(ROTATION_ANGLE)) +
        frameRect.height * cos(optional::performToRadians(ROTATION_ANGLE))), ACCURACY));
}

void testTriangleRotate()
{
  vorotnikov::Triangle triangle({2, 2}, {1, 0}, {5, 3});
  const double area = triangle.getArea();
  vorotnikov::point_t point_one = triangle.getPointOne();
  vorotnikov::point_t point_two = triangle.getPointTwo();
  vorotnikov::point_t point_three = triangle.getPointThree();
  triangle.rotate(ROTATION_ANGLE);
  assert(checkClose(triangle.getArea(), area, ACCURACY));
  assert(checkClose(triangle.getPointOne().x, (point_one.x - triangle.getCenterX()) *
      std::cos(optional::performToRadians(ROTATION_ANGLE)) - (point_one.y - triangle.getCenterY()) *
        std::sin(optional::performToRadians(ROTATION_ANGLE)) + triangle.getCenterX(), ACCURACY));
  assert(checkClose(triangle.getPointOne().y, (point_one.x - triangle.getCenterX()) *
      std::sin(optional::performToRadians(ROTATION_ANGLE)) + (point_one.y - triangle.getCenterY()) *
        std::cos(optional::performToRadians(ROTATION_ANGLE)) + triangle.getCenterY(), ACCURACY));
  assert(checkClose(triangle.getPointTwo().x, (point_two.x - triangle.getCenterX()) *
      std::cos(optional::performToRadians(ROTATION_ANGLE)) - (point_two.y - triangle.getCenterY()) *
        std::sin(optional::performToRadians(ROTATION_ANGLE)) + triangle.getCenterX(), ACCURACY));
  assert(checkClose(triangle.getPointTwo().y, (point_two.x - triangle.getCenterX()) *
      std::sin(optional::performToRadians(ROTATION_ANGLE)) + (point_two.y - triangle.getCenterY()) *
        std::cos(optional::performToRadians(ROTATION_ANGLE)) + triangle.getCenterY(), ACCURACY));
  assert(checkClose(triangle.getPointThree().x, (point_three.x - triangle.getCenterX()) *
      std::cos(optional::performToRadians(ROTATION_ANGLE)) - (point_three.y - triangle.getCenterY()) *
        std::sin(optional::performToRadians(ROTATION_ANGLE)) + triangle.getCenterX(), ACCURACY));
  assert(checkClose(triangle.getPointThree().y, (point_three.x - triangle.getCenterX()) *
      std::sin(optional::performToRadians(ROTATION_ANGLE)) + (point_three.y - triangle.getCenterY()) *
        std::cos(optional::performToRadians(ROTATION_ANGLE)) + triangle.getCenterY(), ACCURACY));
}

void testPolygonRotate()
{
  vorotnikov::Polygon polygon({{0, 0}, {0, 3}, {4, 0}});
  const double area = polygon.getArea();
  vorotnikov::point_t pos = polygon.getPosition();
  const double width = polygon.getFrameRect().width;
  const double height = polygon.getFrameRect().height;
  polygon.rotate(90);
  assert(checkClose(polygon.getArea(), area, ACCURACY));
  assert(checkClose(polygon.getPosition().x, pos.x, ACCURACY));
  assert(checkClose(polygon.getPosition().y, pos.y, ACCURACY));
  assert(checkClose(polygon.getFrameRect().width, height, ACCURACY));
  assert(checkClose(polygon.getFrameRect().height, width, ACCURACY));
}

void testPolygonScale()
{
  vorotnikov::Polygon polygon({{0, 0}, {0, 3}, {4, 0}});
  const double area = polygon.getArea();
  polygon.scale(2);
  assert(checkClose(polygon.getArea(), area * 4, ACCURACY));
}

void testCompositeShapeRotate()
{
  vorotnikov::Rectangle rectangle(4, 2, {2, 5});
  vorotnikov::CompositeShape compositeShape(2);
  std::shared_ptr<vorotnikov::Shape> shape1 = std::make_shared<vorotnikov::Rectangle>(rectangle);
  compositeShape.addShape(shape1);
  vorotnikov::Circle circle(5, {3, 4});
  std::shared_ptr<vorotnikov::Shape> shape2 = std::make_shared<vorotnikov::Circle>(circle);
  compositeShape.addShape(shape2);

  const double area = compositeShape.getArea();
  const vorotnikov::rectangle_t frameRect = compositeShape.getFrameRect();
  compositeShape.rotate(ROTATION_ANGLE);
  assert(checkClose(compositeShape.getArea(), area, ACCURACY));
  assert(checkClose(compositeShape.getFrameRect().pos.x, frameRect.pos.x, ACCURACY));
  assert(checkClose(compositeShape.getFrameRect().pos.y, frameRect.pos.y, ACCURACY));
  assert(
      checkClose(compositeShape.getFrameRect().width, frameRect.width, ACCURACY));
  assert(
      checkClose(compositeShape.getFrameRect().height, frameRect.height, ACCURACY));
}

void testMatrixAddShape()
{
  vorotnikov::Rectangle rectangle(4, 2, {2, 5});
  vorotnikov::Matrix matrix;
  std::shared_ptr<vorotnikov::Shape> shape1 = std::make_shared<vorotnikov::Rectangle>(rectangle);
  matrix.addShape(shape1);
  vorotnikov::Circle circle(5, {3, 4});
  std::shared_ptr<vorotnikov::Shape> shape2 = std::make_shared<vorotnikov::Circle>(circle);
  matrix.addShape(shape2);
  assert(matrix.getShape(0, 0) == shape1);
  assert(matrix.getShape(1, 0) == shape2);
}

void testCompositeShapeToMatrix()
{
  vorotnikov::Rectangle rectangle(4, 2, {2, 5});
  vorotnikov::CompositeShape compositeShape(2);
  std::shared_ptr<vorotnikov::Shape> shape1 = std::make_shared<vorotnikov::Rectangle>(rectangle);
  compositeShape.addShape(shape1);
  vorotnikov::Circle circle(5, {3, 4});
  std::shared_ptr<vorotnikov::Shape> shape2 = std::make_shared<vorotnikov::Circle>(circle);
  compositeShape.addShape(shape2);
  vorotnikov::Matrix matrix = compositeShape.toMatrix();
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
    vorotnikov::Matrix matrix;
    matrix.addShape(nullptr);
  }));
}

void testMatrixShapeInvalidIndex()
{
  std::string testName = "Matrix invalid shape index test";
  assert(checkException<std::out_of_range>([]()
  {
    vorotnikov::Rectangle rectangle(4, 2, {2, 5});
    vorotnikov::Matrix matrix;
    std::shared_ptr<vorotnikov::Shape> shape1 = std::make_shared<vorotnikov::Rectangle>(rectangle);
    matrix.addShape(shape1);
    matrix.getShape(1, 0);
  }));
  assert(checkException<std::out_of_range>([]()
  {
    vorotnikov::Rectangle rectangle(4, 2, {2, 5});
    vorotnikov::Matrix matrix;
    std::shared_ptr<vorotnikov::Shape> shape1 = std::make_shared<vorotnikov::Rectangle>(rectangle);
    matrix.addShape(shape1);
    matrix.getShape(0, 1);
  }));
}

void testPolygonConstructorInvalidArgument()
{
  assert(checkException<std::invalid_argument>([]() {
    vorotnikov::Polygon({{{0, 0}, {10, 1}}});
  }));
  assert(checkException<std::invalid_argument>([]() {
    vorotnikov::Polygon({{0, 0}, {0, 0}, {0, 1}});
  }));
  assert(checkException<std::invalid_argument>([]() {
    vorotnikov::Polygon({{0, 0}, {0, 3}, {1, 1}, {3, 0}});
  }));
};

void testPolygonScaleInvalidArgument()
{
  assert(checkException<std::invalid_argument>([]()
  {
    vorotnikov::Polygon polygon({{0, 0}, {0, 3}, {4, 0}});
    polygon.scale(-1);
  }));

};

int main()
{
  std::vector<std::function<void()>> tests = {
      testCircleRotate, testRectangleRotate, testTriangleRotate, testPolygonConstructorInvalidArgument,
      testPolygonRotate, testCompositeShapeRotate, testMatrixAddShape, testPolygonScale,
      testCompositeShapeToMatrix, testMatrixInvalidShapeToAdd, testMatrixShapeInvalidIndex, testPolygonScaleInvalidArgument
  };
  for (auto &test : tests)
  {
    test();
  }
  return 0;
}
