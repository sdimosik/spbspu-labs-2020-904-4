#include "test-functions.hpp"
#include <stdexcept>
#include <cmath>
#include <memory>

const kichigin::point_t POSITION = { 0.0, 0.0 };
const double EPSILON = 0.0000001;

bool areRectangleParametersConstantAfterMove()
{
  kichigin::point_t pos1 = { 1.0, -1.0 };
  double width = 2.0, height = 3.0;
  kichigin::Rectangle rect(width, height, pos1);
  double area = rect.getArea();
  kichigin::point_t pos2 = { -1.0, 1.0 };
  rect.move(pos2);
  return ((rect.getWidth() == width) && (rect.getHeight() == height) && (rect.getArea() == area));
}

bool areCircleParametersConstantAfterMove()
{
  kichigin::point_t pos1 = { 1.0, -1.0 };
  double radius = 2.0;
  kichigin::Circle circle(radius, pos1);
  double area = circle.getArea();
  kichigin::point_t pos2 = { -1.0, 1.0 };
  circle.move(pos2);
  return ((circle.getRadius() == radius) && (circle.getArea() == area));
}

bool isRectangleAreaChangedSquaredAfrerScale()
{
  kichigin::point_t pos = { 1.0, -1.0 };
  kichigin::Rectangle rect(2.0, 3.0, pos);
  double area = rect.getArea(), coefficient = 3.0;
  rect.scale(coefficient);
  return (std::abs(rect.getArea() - (coefficient * coefficient * area)) < EPSILON);
}

bool isCircleAreaChangedSquaredAfrerScale()
{
  kichigin::point_t pos = { 1.0, -1.0 };
  kichigin::Circle circle(3.0, pos);
  double area = circle.getArea(), coefficient = 2.0;
  circle.scale(coefficient);
  return (std::abs(circle.getArea() - (coefficient * coefficient * area)) < EPSILON);
}

bool doesRectangleConstructorWorkCorrectWithUncorrectParameters()
{
  try
  {
    kichigin::Rectangle(-1.0, 1.0, POSITION);
    return false;
  }
  catch (const std::invalid_argument& exception)
  {}
  try
  {
    kichigin::Rectangle(0.0, 1.0, POSITION);
    return false;
  }
  catch (const std::invalid_argument& exception)
  {}
  try
  {
    kichigin::Rectangle(1.0, -1.0, POSITION);
    return false;
  }
  catch (const std::invalid_argument& exception)
  {}
  try
  {
    kichigin::Rectangle(1.0, 0.0, POSITION);
    return false;
  }
  catch (const std::invalid_argument& exception)
  {}
  return true;
}

bool doesRectangleSetWidthWorkCorrectWithUncorrectParameters()
{
  kichigin::Rectangle rect(1.0, 1.0, POSITION);
  try
  {
    rect.setWidth(-1.0);
    return false;
  }
  catch (const std::invalid_argument& exception)
  {}
  try
  {
    rect.setWidth(0.0);
    return false;
  }
  catch (const std::invalid_argument& exception)
  {}
  return true;
}

bool doesRectangleSetHeighthWorkCorrectWithUncorrectParameters()
{
  kichigin::Rectangle rect(1.0, 1.0, POSITION);
  try
  {
    rect.setHeight(-1.0);
    return false;
  }
  catch (const std::invalid_argument& exception)
  {}
  try
  {
    rect.setHeight(0.0);
    return false;
  }
  catch (const std::invalid_argument& exception)
  {}
  return true;
}

bool doesRectangleScalehWorkCorrectWithUncorrectParameters()
{
  kichigin::Rectangle rect(1.0, 1.0, POSITION);
  try
  {
    rect.scale(-2.0);
    return false;
  }
  catch (const std::invalid_argument& exception)
  {}
  try
  {
    rect.scale(0.0);
    return false;
  }
  catch (const std::invalid_argument& exception)
  {}
  return true;
}

bool doesCircleConstructorWorkCorrectWithUncorrectParameters()
{
  try
  {
    kichigin::Circle(-1.0, POSITION);
    return false;
  }
  catch (const std::invalid_argument& exception)
  {}
  try
  {
    kichigin::Circle(0.0, POSITION);
    return false;
  }
  catch (const std::invalid_argument& exception)
  {}
  return true;
}

bool doesCircleSetRadiusWorkCorrectWithUncorrectParameters()
{
  kichigin::Circle circle(1.0, POSITION);
  try
  {
    circle.setRadius(-1.0);
    return false;
  }
  catch (const std::invalid_argument& exception)
  {}
  try
  {
    circle.setRadius(0.0);
    return false;
  }
  catch (const std::invalid_argument& exception)
  {}
  return true;
}

bool doesCircleScaleWorkCorrectWithUncorrectParameters()
{
  kichigin::Circle circle(1.0, POSITION);
  try
  {
    circle.scale(-1.0);
    return false;
  }
  catch (const std::invalid_argument& exception)
  {}
  try
  {
    circle.scale(0.0);
    return false;
  }
  catch (const std::invalid_argument& exception)
  {}
  return true;
}

bool doesCompositeShapeAddShapeWorkCorrectWithUncorrectParameters()
{
  kichigin::CompositeShape compShape;
  std::shared_ptr<kichigin::Shape> shape(nullptr);
  try
  {
    compShape.addShape(shape);
  }
  catch (const std::invalid_argument& exception)
  {
    return true;
  }
  return false;
}

bool doesCompositeShapeDeleteShapeWorkCorrectWithUncorrectParameters()
{
  kichigin::Rectangle rect(1.0, 1.0, POSITION);
  std::shared_ptr<kichigin::Shape> shape = std::make_shared<kichigin::Rectangle>(rect);
  kichigin::CompositeShape compShape;
  try
  {
    compShape.deleteShape(1);
  }
  catch (const std::out_of_range& exception)
  {
    compShape.addShape(shape);
    try
    {
      compShape.deleteShape(2);
    }
    catch (const std::out_of_range& exception)
    {
      return true;
    }
  }
  return false;
}

bool doesCompositeShapeOperatorIndexWorkCorrectWithUncorrectParameters()
{
  kichigin::CompositeShape compShape;
  try
  {
    compShape[0];
  }
  catch (const std::out_of_range& exception)
  {
    try
    {
      compShape[1];
    }
    catch (const std::out_of_range& exception)
    {
      return true;
    }
  }
  return false;
}

bool areCompositeShapeParametersConstantAfterMove()
{
  kichigin::Rectangle rect(1.0, 3.0, POSITION);
  std::shared_ptr<kichigin::Shape> shape = std::make_shared<kichigin::Rectangle>(rect);
  kichigin::CompositeShape compShape(2);
  compShape.addShape(shape);
  kichigin::Circle circle(2.0, POSITION);
  shape = std::make_shared<kichigin::Circle>(circle);
  compShape.addShape(shape);
  kichigin::rectangle_t prevFrame = compShape.getFrameRect();
  double prevRectArea = rect.getArea(), prevCircleArea = circle.getArea();
  compShape.move(1.0, 2.0);
  kichigin::rectangle_t currentFrame = compShape.getFrameRect();
  return (prevFrame.height == currentFrame.height) && (prevFrame.height == currentFrame.height) &&
      (prevRectArea == rect.getArea()) && (prevCircleArea == circle.getArea());
}

bool isCompositeShapeAreaChangedSquaredAfrerScale()
{
  kichigin::Rectangle rect(1.0, 3.0, POSITION);
  std::shared_ptr<kichigin::Shape> shape = std::make_shared<kichigin::Rectangle>(rect);
  kichigin::CompositeShape compShape(2);
  compShape.addShape(shape);
  kichigin::Circle circle(2.0, POSITION);
  shape = std::make_shared<kichigin::Circle>(circle);
  compShape.addShape(shape);
  double prevArea0 = compShape[0]->getArea(), prevArea1 = compShape[1]->getArea();
  const double coefficient = 2.0;
  compShape.scale(coefficient);
  return (std::abs(compShape[0]->getArea() - (coefficient * coefficient * prevArea0)) < EPSILON) &&
      (std::abs(compShape[1]->getArea() - (coefficient * coefficient * prevArea1)) < EPSILON);
}
