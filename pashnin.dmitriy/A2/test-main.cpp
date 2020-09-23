
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

#include <cassert>
#include <cmath>
#include <functional>
#include <vector>
#include <string>

typedef void (*func)();

const double ACCURACY = 0.00001;

bool biasCheckClose(double val1, double val2, double acc)
{
  return std::abs(val1 - val2) < acc;
}

void testRectangleMove()
{
  std::string testName = "Rectangle moving test";
  pashnin::Rectangle rectangle(9.5, 7.25, {8, 1});
  pashnin::rectangle_t frame = rectangle.getFrameRect();
  const double area = rectangle.getArea();
  
  rectangle.move(-152.671, 8922.512);
  assert(biasCheckClose(rectangle.getFrameRect().width, frame.width, ACCURACY));
  assert(biasCheckClose(rectangle.getFrameRect().height, frame.height, ACCURACY));
  assert(biasCheckClose(rectangle.getArea(), area, ACCURACY));
  
  rectangle.move({60.67, -28.0});
  assert(biasCheckClose(rectangle.getFrameRect().width, frame.width, ACCURACY));
  assert(biasCheckClose(rectangle.getFrameRect().height, frame.height, ACCURACY));
  assert(biasCheckClose(rectangle.getArea(), area, ACCURACY));
}

void testRectangleScale()
{
  std::string testName = "Rectangle scaling test";
  pashnin::Rectangle rectangle(164.52, 89.1, {-19.6, 55.2});
  const double area = rectangle.getArea();
  const double factor = 1.58;
  rectangle.scale(factor);
  assert(biasCheckClose(area * factor * factor, rectangle.getArea(), ACCURACY));
}

void testCircleMove()
{
  std::string testName = "Circle moving test";
  pashnin::Circle circle(5, {-6, 4});
  pashnin::rectangle_t frame = circle.getFrameRect();
  const double area = circle.getArea();
  
  circle.move(-152.671, 8922.512);
  assert(biasCheckClose(circle.getFrameRect().width, frame.width, ACCURACY));
  assert(biasCheckClose(circle.getFrameRect().height, frame.height, ACCURACY));
  assert(biasCheckClose(circle.getArea(), area, ACCURACY));
  
  circle.move({60.67, -28.0});
  assert(biasCheckClose(circle.getFrameRect().width, frame.width, ACCURACY));
  assert(biasCheckClose(circle.getFrameRect().height, frame.height, ACCURACY));
  assert(biasCheckClose(circle.getArea(), area, ACCURACY));
}

void testCircleScale()
{
  std::string testName = "Circle scaling test";
  pashnin::Circle circle(5.23, {1, 1});
  const double area = circle.getArea();
  const double factor = 1.58;
  circle.scale(factor);
  assert(biasCheckClose(factor * factor * area, circle.getArea(), ACCURACY));
}

void testTriangleMove()
{
  std::string testName = "Triangle moving test";
  pashnin::Triangle triangle({0, 2}, {2, 0}, {0, 0});
  pashnin::rectangle_t frame = triangle.getFrameRect();
  const double area = triangle.getArea();
  
  triangle.move(-152.671, 8922.512);
  assert(biasCheckClose(triangle.getFrameRect().width, frame.width, ACCURACY));
  assert(biasCheckClose(triangle.getFrameRect().height, frame.height, ACCURACY));
  assert(biasCheckClose(triangle.getArea(), area, ACCURACY));
  
  triangle.move({60.67, -28.0});
  assert(biasCheckClose(triangle.getFrameRect().width, frame.width, ACCURACY));
  assert(biasCheckClose(triangle.getFrameRect().height, frame.height, ACCURACY));
  assert(biasCheckClose(triangle.getArea(), area, ACCURACY));
}

void testTriangleScale()
{
  std::string testName = "Triangle scaling test";
  pashnin::Triangle triangle({0, 2}, {2, 0}, {0, 0});
  const double area = triangle.getArea();
  const double factor = 1.58;
  triangle.scale(factor);
  assert(biasCheckClose(factor * factor * area, triangle.getArea(), ACCURACY));
}

template<class T>
bool checkException(func function)
{
  try
  {
    function();
  }
  catch (T &except)
  {
    return true;
  }
  catch (std::exception &except)
  {
  
  }
  return false;
}

void testInvalidRectangleWidth()
{
  std::string testName = "Rectangle invalid width test";
  assert(checkException<std::invalid_argument>([]()
  {
    pashnin::Rectangle rectangle(-2, 1, {1, 1});
  }));
}

void testInvalidRectangleHeight()
{
  std::string testName = "Rectangle invalid height test";
  assert(checkException<std::invalid_argument>([]()
  {
    pashnin::Rectangle rectangle(1, -2, {1, 1});
  }));
}

void testInvalidRectangleScaling()
{
  std::string testName = "Rectangle invalid scaling test";
  assert(checkException<std::invalid_argument>([]()
  {
    pashnin::Rectangle rectangle(1, 1, {1, 1});
    rectangle.scale(-2);
  }));
}

void testInvalidCircleRadius()
{
  std::string testName = "Circle invalid radius test";
  assert(checkException<std::invalid_argument>([]()
  {
    pashnin::Circle circle(-2, {1, 1});
  }));
}

void testInvalidCircleScaling()
{
  std::string testName = "Circle invalid scaling test";
  assert(checkException<std::invalid_argument>([]()
  {
    pashnin::Circle circle(1, {1, 1});
    circle.scale(-2);
  }));
}

void testInvalidTriangleTopsTheSame()
{
  std::string testName = "Triangle invalid two-tops-are-the-same test";
  assert(checkException<std::invalid_argument>([]()
  {
    pashnin::Triangle triangle({2 ,2}, {2 ,2}, {1, 1});
  }));
}

void testInvalidTriangleTopsOnOneLine()
{
  std::string testName = "Triangle invalid tops-on-one-line test";
  assert(checkException<std::invalid_argument>([]()
  {
    pashnin::Triangle triangle({-2 ,-2}, {0 ,0}, {2 ,2});
  }));
}

void testInvalidTriangleScaling()
{
  std::string testName = "Triangle invalid scaling test";
  assert(checkException<std::invalid_argument>([]()
  {
    pashnin::Triangle triangle({0 ,1}, {1 ,0}, {0 ,0});
    triangle.scale(-2);
  }));
}

int main()
{
  std::vector<std::function<void()>> tests = {
    testRectangleMove,
    testRectangleScale,
    testCircleMove,
    testCircleScale,
    testTriangleMove,
    testTriangleScale,
    testInvalidRectangleWidth,
    testInvalidRectangleHeight,
    testInvalidRectangleScaling,
    testInvalidCircleRadius,
    testInvalidCircleScaling,
    testInvalidTriangleTopsTheSame,
    testInvalidTriangleTopsOnOneLine,
    testInvalidTriangleScaling
  };
  for (auto &test : tests)
  {
    test();
  }
  return 0;
}
