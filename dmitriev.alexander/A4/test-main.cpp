#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "utils.hpp"

#include <cmath>
#include <string>
#include <cassert>
#include <vector>
#include <functional>
#include <matrix.hpp>

typedef void (*func)();

const double ACCURACY = .001;
const double ROTATION_ANGLE = 15;

bool checkClose(double val1, double val2, double acc)
{
  return std::abs(val1 - val2) < acc;
}

void testCircleRotate()
{
  std::string testName = "Circle rotate test";
  dmitriev::Circle circle({2, 0}, 4);
  const double area = circle.getArea();
  const dmitriev::rectangle_t frameRect = circle.getFrameRect();
  circle.rotate(ROTATION_ANGLE);

  assert(checkClose(circle.getArea(), area, ACCURACY));
  assert(checkClose(circle.getFrameRect().pos.x, frameRect.pos.x, ACCURACY));
  assert(checkClose(circle.getFrameRect().pos.y, frameRect.pos.y, ACCURACY));
}

void testRectangleRotate()
{
  std::string testName = "Rectangle rotate test";
  dmitriev::Rectangle rectangle({2, 2}, 2, 4);
  const double area = rectangle.getArea();
  const dmitriev::rectangle_t frameRect = rectangle.getFrameRect();
  rectangle.rotate(ROTATION_ANGLE);

  assert(checkClose(rectangle.getArea(), area, ACCURACY));
  assert(checkClose(rectangle.getFrameRect().pos.x, frameRect.pos.x, ACCURACY));
  assert(checkClose(rectangle.getFrameRect().pos.y, frameRect.pos.y, ACCURACY));
  assert(
    checkClose(rectangle.getFrameRect().width,
      frameRect.width * fabs(cos(utils::toRadians(ROTATION_ANGLE))) +
      frameRect.height * fabs(sin(utils::toRadians(ROTATION_ANGLE))), ACCURACY));
  assert(
    checkClose(rectangle.getFrameRect().height,
      frameRect.width * fabs(sin(utils::toRadians(ROTATION_ANGLE))) +
      frameRect.height * fabs(cos(utils::toRadians(ROTATION_ANGLE))), ACCURACY));
}

void testCompositeShapeRotate()
{
  std::string testName = "Composite shape rotate test";
  dmitriev::Rectangle rectangle({2, 5}, 4, 2);
  dmitriev::CompositeShape compositeShape(2);
  std::shared_ptr<dmitriev::Shape> shape1 = std::make_shared<dmitriev::Rectangle>(rectangle);
  compositeShape.addShape(shape1);
  dmitriev::Circle circle({3, 4}, 5);
  std::shared_ptr<dmitriev::Shape> shape2 = std::make_shared<dmitriev::Circle>(circle);
  compositeShape.addShape(shape2);

  const double area = compositeShape.getArea();
  const dmitriev::rectangle_t frameRect = compositeShape.getFrameRect();
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
  std::string testName = "Matrix add shape test";
  dmitriev::Rectangle rectangle({2, 5}, 4, 2);
  dmitriev::Matrix matrix;
  std::shared_ptr<dmitriev::Shape> shape1 = std::make_shared<dmitriev::Rectangle>(rectangle);
  matrix.addShape(shape1);
  dmitriev::Circle circle({3, 4}, 5);
  std::shared_ptr<dmitriev::Shape> shape2 = std::make_shared<dmitriev::Circle>(circle);
  matrix.addShape(shape2);
  assert(matrix.getShape(0, 0) == shape1);
  assert(matrix.getShape(1, 0) == shape2);
}

void testCompositeShapeToMatrix()
{
  std::string testName = "Composite shape to matrix test";
  dmitriev::Rectangle rectangle({2, 5}, 4, 2);
  dmitriev::CompositeShape compositeShape(2);
  std::shared_ptr<dmitriev::Shape> shape1 = std::make_shared<dmitriev::Rectangle>(rectangle);
  compositeShape.addShape(shape1);
  dmitriev::Circle circle({3, 4}, 5);
  std::shared_ptr<dmitriev::Shape> shape2 = std::make_shared<dmitriev::Circle>(circle);
  compositeShape.addShape(shape2);
  dmitriev::Matrix matrix = compositeShape.toMatrix();
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
    dmitriev::Matrix matrix;
    matrix.addShape(nullptr);
  }));
}

void testMatrixShapeInvalidIndex()
{
  std::string testName = "Matrix invalid shape index test";
  assert(checkException<std::out_of_range>([]()
  {
    dmitriev::Rectangle rectangle({2, 5}, 4, 2);
    dmitriev::Matrix matrix;
    std::shared_ptr<dmitriev::Shape> shape1 = std::make_shared<dmitriev::Rectangle>(rectangle);
    matrix.addShape(shape1);
    matrix.getShape(1, 0);
  }));
  assert(checkException<std::out_of_range>([]()
  {
    dmitriev::Rectangle rectangle({2, 5}, 4, 2);
    dmitriev::Matrix matrix;
    std::shared_ptr<dmitriev::Shape> shape1 = std::make_shared<dmitriev::Rectangle>(rectangle);
    matrix.addShape(shape1);
    matrix.getShape(0, 1);
  }));
}

int main()
{
  std::vector<std::function<void()>> tests = {
    testCircleRotate, testRectangleRotate, testCompositeShapeRotate,
    testMatrixAddShape, testCompositeShapeToMatrix, testMatrixInvalidShapeToAdd,
    testMatrixShapeInvalidIndex
  };
  for (auto &test : tests)
  {
    test();
  }
  return 0;
}
