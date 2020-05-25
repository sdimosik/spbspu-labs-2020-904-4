#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

#include <cmath>
#include <string>
#include <cassert>
#include <vector>
#include <functional>

typedef void (*func)();

const double ACCURACY = .001;

bool checkClose(double val1, double val2, double acc)
{
  return std::abs(val1 - val2) < acc;
}

void testCompositeShapeAddShape()
{
  std::string testName = "Composite shape add new shape test";
  dmitriev::Rectangle rectangle({0, 0}, 2, 4);
  dmitriev::CompositeShape compositeShape(2);
  std::shared_ptr<dmitriev::Shape> shape = std::make_shared<dmitriev::Rectangle>(rectangle);
  compositeShape.addShape(shape);
  assert(compositeShape.getSize() == 1);
  assert(compositeShape[0] == shape);
}

void testCompositeShapeRemoveShape()
{
  std::string testName = "Composite shape remove shape test";
  dmitriev::Rectangle rectangle({0, 0}, 2, 4);
  dmitriev::CompositeShape compositeShape(2);
  std::shared_ptr<dmitriev::Shape> shape = std::make_shared<dmitriev::Rectangle>(rectangle);
  compositeShape.addShape(shape);
  compositeShape.removeShape(0);
  assert(compositeShape.getSize() == 0);
}

void testCompositeShapeGetArea()
{
  std::string testName = "Composite shape get area of all shapes test";
  dmitriev::Rectangle rectangle({0, 0}, 2, 4);
  dmitriev::Circle circle({0, 0}, 5);
  dmitriev::CompositeShape compositeShape(2);
  std::shared_ptr<dmitriev::Shape> shape1 = std::make_shared<dmitriev::Rectangle>(rectangle);
  compositeShape.addShape(shape1);
  std::shared_ptr<dmitriev::Shape> shape2 = std::make_shared<dmitriev::Circle>(circle);
  compositeShape.addShape(shape2);
  assert(checkClose(compositeShape.getArea(), shape1->getArea() + shape2->getArea(), ACCURACY));
}

void testCompositeShapeGetFrameRect()
{
  std::string testName = "Composite shape get frame rect of shapes test";
  dmitriev::Rectangle rectangle({0, 0}, 2, 4);
  dmitriev::Circle circle({5, 5}, 5);
  dmitriev::CompositeShape compositeShape(2);
  std::shared_ptr<dmitriev::Shape> shape1 = std::make_shared<dmitriev::Rectangle>(rectangle);
  compositeShape.addShape(shape1);
  std::shared_ptr<dmitriev::Shape> shape2 = std::make_shared<dmitriev::Circle>(circle);
  compositeShape.addShape(shape2);
  dmitriev::rectangle_t rectFrame = shape1->getFrameRect();
  dmitriev::rectangle_t circleFrame = shape2->getFrameRect();
  assert(checkClose(compositeShape.getFrameRect().height,
    circleFrame.pos.y + circleFrame.height / 2 - (rectFrame.pos.y - rectFrame.height / 2), ACCURACY));
  assert(checkClose(compositeShape.getFrameRect().width,
    circleFrame.pos.x + circleFrame.width / 2 - (rectFrame.pos.x - rectFrame.width / 2), ACCURACY));
  assert(checkClose(compositeShape.getFrameRect().pos.x,
    rectFrame.pos.x - rectFrame.width / 2 + compositeShape.getFrameRect().width / 2, ACCURACY));
  assert(checkClose(compositeShape.getFrameRect().pos.y,
    rectFrame.pos.y - rectFrame.height / 2 + compositeShape.getFrameRect().height / 2, ACCURACY));
}

void testCompositeShapeMove()
{
  std::string testName = "Composite shape move shapes test";
  dmitriev::Rectangle rectangle({0, 0}, 2, 4);
  dmitriev::Circle circle({0, 0}, 5);
  dmitriev::CompositeShape compositeShape(2);
  std::shared_ptr<dmitriev::Shape> shape1 = std::make_shared<dmitriev::Rectangle>(rectangle);
  compositeShape.addShape(shape1);
  std::shared_ptr<dmitriev::Shape> shape2 = std::make_shared<dmitriev::Circle>(circle);
  compositeShape.addShape(shape2);
  dmitriev::rectangle_t oldFrame = compositeShape.getFrameRect();
  compositeShape.move(2, 2);
  assert(checkClose(compositeShape.getFrameRect().pos.x, oldFrame.pos.x + 2, ACCURACY));
  assert(checkClose(compositeShape.getFrameRect().pos.y, oldFrame.pos.y + 2, ACCURACY));
  compositeShape.move({4, 4});
  assert(checkClose(compositeShape.getFrameRect().pos.x, oldFrame.pos.x + 4, ACCURACY));
  assert(checkClose(compositeShape.getFrameRect().pos.y, oldFrame.pos.y + 4, ACCURACY));
  assert(checkClose(compositeShape.getFrameRect().width, oldFrame.width, ACCURACY));
  assert(checkClose(compositeShape.getFrameRect().height, oldFrame.height, ACCURACY));
}

void testCompositeShapeScale()
{
  std::string testName = "Composite shape scale shapes test";
  dmitriev::Rectangle rectangle({0, 0}, 2, 4);
  dmitriev::Circle circle({0, 0}, 5);
  dmitriev::CompositeShape compositeShape(2);
  std::shared_ptr<dmitriev::Shape> shape1 = std::make_shared<dmitriev::Rectangle>(rectangle);
  compositeShape.addShape(shape1);
  std::shared_ptr<dmitriev::Shape> shape2 = std::make_shared<dmitriev::Circle>(circle);
  compositeShape.addShape(shape2);
  const double area = compositeShape.getArea();
  const double scaleFactor = 1.75;
  compositeShape.scale(scaleFactor);
  assert(checkClose(area * scaleFactor * scaleFactor, compositeShape.getArea(), ACCURACY));
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

void testCompositeShapeInvalidCapacity()
{
  std::string testName = "Composite shape invalid capacity test";
  assert(checkException<std::out_of_range>([]()
  {
    dmitriev::CompositeShape compositeShape(0);
  }));
}

void testCompositeShapeInvalidIndex()
{
  std::string testName = "Composite shape invalid index test";
  assert(checkException<std::out_of_range>([]()
  {
    dmitriev::CompositeShape compositeShape(1);
    compositeShape[0];
  }));
  assert(checkException<std::out_of_range>([]()
  {
    dmitriev::CompositeShape compositeShape(1);
    compositeShape.removeShape(0);
  }));
}

void testCompositeShapeInvalidShapeToAdd()
{
  std::string testName = "Composite shape invalid shape to add test";
  assert(checkException<std::invalid_argument>([]()
  {
    dmitriev::CompositeShape compositeShape(1);
    compositeShape.addShape(nullptr);
  }));
}

void testCompositeShapeInvalidScaleFactor()
{
  std::string testName = "Composite shape invalid scale factor test";
  assert(checkException<std::invalid_argument>([]()
  {
    dmitriev::CompositeShape compositeShape(1);
    compositeShape.scale(0);
  }));
}

int main()
{
  std::vector<std::function<void()>> tests = {
    testCompositeShapeAddShape, testCompositeShapeRemoveShape, testCompositeShapeGetArea,
    testCompositeShapeGetFrameRect, testCompositeShapeMove, testCompositeShapeScale,
    testCompositeShapeInvalidCapacity, testCompositeShapeInvalidIndex, testCompositeShapeInvalidShapeToAdd,
    testCompositeShapeInvalidScaleFactor
  };
  for (auto &test : tests)
  {
    test();
  }
  return 0;
}
