#include "test-functions.hpp"
#include <stdexcept>
#include <cmath>
#include <memory>

const kichigin::point_t POSITION = { 0.0, 0.0 };
const double EPSILON = 0.0000001;

bool doesRectangleRotateWorksCorrect()
{
  kichigin::Rectangle rect(2.0, 2.0, POSITION);
  double angle = 45;
  rect.rotate(angle);
  angle = angle * M_PI / 180;
  kichigin::rectangle_t frame = rect.getFrameRect();
  return (std::abs(2 * std::abs(std::cos(angle)) + 2 * std::abs(std::sin(angle)) - frame.width) < EPSILON
      && (2 * std::abs(std::sin(angle)) + 2 * std::abs(std::cos(angle)) - frame.height) < EPSILON);
}

bool doesCircleRotateWorksCorrect()
{
  kichigin::Circle circle(2.0, POSITION);
  double angle = 45;
  circle.rotate(angle);
  kichigin::rectangle_t frame = circle.getFrameRect();
  return (std::abs(2.0 * 2 * 2.0 * 2 - frame.width * frame.height) < EPSILON);
}

bool doesCompositeShapeRotateWorksCorrect()
{
  kichigin::Rectangle rect(2.0, 2.0, POSITION);
  std::shared_ptr<kichigin::Shape> sharedPointer = std::make_shared<kichigin::Rectangle>(rect);
  kichigin::CompositeShape compShape;
  compShape.addShape(sharedPointer);
  kichigin::Circle circle(2.0, POSITION);
  sharedPointer = std::make_shared<kichigin::Circle>(circle);
  compShape.addShape(sharedPointer);
  double angle = 45;
  compShape.rotate(angle);
  kichigin::rectangle_t frame1 = compShape[0]->getFrameRect();
  kichigin::rectangle_t frame2 = compShape[1]->getFrameRect();
  angle = angle * M_PI / 180;
  return (std::abs(2 * std::abs(std::cos(angle)) + 2 * std::abs(std::sin(angle)) - frame1.width) < EPSILON
        && (2 * std::abs(std::sin(angle)) + 2 * std::abs(std::cos(angle)) - frame1.height) < EPSILON)
      && (std::abs(2.0 * 2 * 2.0 * 2 - frame2.width * frame2.height) < EPSILON);
}

bool doesMatrixGetShapeWorkCorrectWithUncorrectParameters()
{
  kichigin::Rectangle rect1(2.0, 2.0, POSITION);
  kichigin::Rectangle rect2(1.0, 1.0, POSITION);
  rect2.move(2.0, 2.0);
  kichigin::Rectangle rect3(1.0, 1.0, POSITION);
  rect3.move(4.0, -2.0);
  std::shared_ptr<kichigin::Shape> shape1 = std::make_shared<kichigin::Rectangle>(rect1);
  std::shared_ptr<kichigin::Shape> shape2 = std::make_shared<kichigin::Rectangle>(rect2);
  std::shared_ptr<kichigin::Shape> shape3 = std::make_shared<kichigin::Rectangle>(rect3);
  kichigin::Matrix matrix(3);
  matrix.addShape(shape1);
  matrix.addShape(shape2);
  matrix.addShape(shape3);
  try
  {
    matrix.getShape(2, 0);
  }
  catch (const std::out_of_range& error)
  {
    try
    {
      matrix.getShape(1,1);
    }
    catch (const std::exception&)
    {
      return true;
    }
  }
  return false;
}

bool doesMatrixGetLayerCurrentSizeWorkCorrectWithUncorrectParameters()
{
  kichigin::Matrix matrix(1);
  try
  {
    matrix.getLayerCurrentSize(0);
  }
  catch (const std::out_of_range& error)
  {
    try
    {
      kichigin::Rectangle rect(2.0, 2.0, POSITION);
      std::shared_ptr<kichigin::Shape> shape = std::make_shared<kichigin::Rectangle>(rect);
      matrix.addShape(shape);
      matrix.getLayerCurrentSize(1);
    }
    catch (const std::out_of_range& error)
    {
      return true;
    }
  }
  return false;
}
