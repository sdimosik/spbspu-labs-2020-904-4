#include "test-functions.hpp"
#include <stdexcept>
#include <cmath>

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
