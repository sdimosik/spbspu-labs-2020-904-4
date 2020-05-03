#include "circle.hpp"
#include "rectangle.hpp"

#include <cmath>
#include <string>
#include <cassert>
#include <vector>
#include <functional>

typedef void (*func)();

const double ACCURACY = .00001;

bool checkClose(double val1, double val2, double acc)
{
  return std::abs(val1 - val2) < acc;
}

void testCircleMove()
{
  dmitriev::Circle circle(dmitriev::point_t{0, 0}, 4);
  dmitriev::rectangle_t frameRect = circle.getFrameRect();
  const double area = circle.getArea();

  circle.move(10.3, -17.9);
  assert(checkClose(circle.getFrameRect().width, frameRect.width, ACCURACY));
  assert(checkClose(circle.getFrameRect().height, frameRect.height, ACCURACY));
  assert(checkClose(circle.getArea(), area, ACCURACY));

  circle.move({60.67, -28.0});
  assert(checkClose(circle.getFrameRect().width, frameRect.width, ACCURACY));
  assert(checkClose(circle.getFrameRect().height, frameRect.height, ACCURACY));
  assert(checkClose(circle.getArea(), area, ACCURACY));
}

void testRectMove()
{
  dmitriev::Rectangle rect(dmitriev::point_t{10, -10}, 4, 2);
  dmitriev::rectangle_t frameRect = rect.getFrameRect();
  const double area = rect.getArea();

  rect.move(92, 67.1);
  assert(checkClose(rect.getFrameRect().width, frameRect.width, ACCURACY));
  assert(checkClose(rect.getFrameRect().height, frameRect.height, ACCURACY));
  assert(checkClose(rect.getArea(), area, ACCURACY));

  rect.move({-182.3, -12.8});
  assert(checkClose(rect.getFrameRect().width, frameRect.width, ACCURACY));
  assert(checkClose(rect.getFrameRect().height, frameRect.height, ACCURACY));
  assert(checkClose(rect.getArea(), area, ACCURACY));
}

void testCircleScale()
{
  std::string testName = "Circle scaling test";
  dmitriev::Circle circle(dmitriev::point_t{0, 0}, 4);
  const double area = circle.getArea();
  const double scaleFactor = 1.75;
  circle.scale(scaleFactor);
  assert(checkClose(area * scaleFactor * scaleFactor, circle.getArea(), ACCURACY));
}

void testRectScale()
{
  std::string testName = "Rectangle scaling test";
  dmitriev::Rectangle rect(dmitriev::point_t{0, 0}, 4, 10);
  const double area = rect.getArea();
  const double scaleFactor = 1.75;
  rect.scale(scaleFactor);
  assert(checkClose(area * scaleFactor * scaleFactor, rect.getArea(), ACCURACY));
}

template <class T>
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

void testInvalidCircleRadius()
{
  std::string testName = "Circle invalid radius test";
  assert(checkException<std::invalid_argument>([]()
    {
      dmitriev::Circle({0, 0}, -3);
    }));
}

void testInvalidRectangleWidth()
{
  std::string testName = "Rectangle invalid width test";
  assert(checkException<std::invalid_argument>([]()
    { dmitriev::Rectangle({0, 0}, -3, 4); }));
}

void testInvalidRectangleHeight()
{
  std::string testName = "Rectangle invalid height test";
  assert(checkException<std::invalid_argument>([]()
    { dmitriev::Rectangle({0, 0}, 2, -4); }));
}

void testInvalidCircleScaling()
{
  std::string testName = "Circle invalid scaling test";
  assert(checkException<std::invalid_argument>([]()
    {
      dmitriev::Circle circle({0, 0}, 3);
      circle.scale(-10);
    }));
}

void testInvalidRectangleScaling()
{
  std::string testName = "Rectangle invalid scaling test";
  assert(checkException<std::invalid_argument>([]()
    {
      dmitriev::Rectangle rect({0, 0}, 2, 4);
      rect.scale(-13.3);
    }));
}

int main()
{
  std::vector<std::function<void()>> tests = {
    testCircleMove, testRectMove, testCircleScale,
    testRectScale, testInvalidCircleRadius, testInvalidRectangleWidth,
    testInvalidRectangleHeight, testInvalidCircleScaling, testInvalidRectangleScaling
  };
  for(auto & test : tests)
  {
    test();
  }
  return 0;
}
