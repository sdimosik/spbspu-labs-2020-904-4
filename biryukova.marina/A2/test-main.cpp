#define BOOST_TEST_MODULE TEST_A2
#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"

const double ACCURACY_DOUBLE = 0.00001;

BOOST_AUTO_TEST_CASE(constancyParametersAfterMoveCircle)
{
  biryukova::Circle circle(biryukova::point_t{1.8, 4.2}, 8.1);
  const double areaCircle = circle.getArea();
  const double radiusCircle = circle.getRadius();
  circle.move(biryukova::point_t{3.0, 7.1});
  BOOST_CHECK_CLOSE(areaCircle, circle.getArea(), ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(radiusCircle, circle.getRadius(), ACCURACY_DOUBLE);
  circle.move(1.0, 2.0);
  BOOST_CHECK_CLOSE(areaCircle, circle.getArea(), ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(radiusCircle, circle.getRadius(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(constancyParametersAfterMoveRectangle)
{
  biryukova::Rectangle rectangle(biryukova::point_t{3.0, 7.1}, 9.4, 2.4);
  const double areaRectangle = rectangle.getArea();
  const double heightRectangle = rectangle.getHeight();
  const double widthRectangle = rectangle.getWidth();
  rectangle.move(biryukova::point_t{3.9, 7.2});
  BOOST_CHECK_CLOSE(areaRectangle, rectangle.getArea(), ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(heightRectangle, rectangle.getHeight(), ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(widthRectangle, rectangle.getWidth(), ACCURACY_DOUBLE);
  rectangle.move(1.0, 2.0);
  BOOST_CHECK_CLOSE(areaRectangle, rectangle.getArea(), ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(heightRectangle, rectangle.getHeight(), ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(widthRectangle, rectangle.getWidth(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(areaAfterScaleCircle)
{
  biryukova::Circle circle(biryukova::point_t{1.8, 4.2}, 8.1);
  double coefficient = 3.0;
  double areaCircle = circle.getArea() * coefficient * coefficient;
  circle.scale(coefficient);
  BOOST_CHECK_CLOSE(areaCircle, circle.getArea(), ACCURACY_DOUBLE);
  coefficient = 0.5;
  areaCircle = circle.getArea() * coefficient * coefficient;
  circle.scale(coefficient);
  BOOST_CHECK_CLOSE(areaCircle, circle.getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(areaAfterScaleRectangle)
{
  biryukova::Rectangle rectangle(biryukova::point_t{3.0, 7.1}, 9.4, 2.4);
  double coefficient = 3.0;
  double areaRectangle = rectangle.getArea() * coefficient * coefficient;
  rectangle.scale(coefficient);
  BOOST_CHECK_CLOSE(areaRectangle, rectangle.getArea(), ACCURACY_DOUBLE);
  coefficient = 0.5;
  areaRectangle = rectangle.getArea() * coefficient * coefficient;
  rectangle.scale(coefficient);
  BOOST_CHECK_CLOSE(areaRectangle, rectangle.getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(invalidParameterCircle)
{
  BOOST_CHECK_THROW(biryukova::Circle circle(biryukova::point_t{1.8, 4.2}, -8.1), 
      std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalidHeightRectangle)
{
  BOOST_CHECK_THROW(biryukova::Rectangle rectangle(biryukova::point_t{3.0, 7.1}, 9.4, -2.4),
      std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalidWidthRectangle)
{
  BOOST_CHECK_THROW(biryukova::Rectangle rectangle(biryukova::point_t{3.0, 7.1}, -9.4, 2.4),
      std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalidParameterScaleCircle)
{
  biryukova::Circle circle(biryukova::point_t{1.8, 4.2}, 8.1);
  BOOST_CHECK_THROW(circle.scale(-3.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalidParameterScaleRectangle)
{
  biryukova::Rectangle rectangle(biryukova::point_t{3.0, 7.1}, 9.4, 2.4);
  BOOST_CHECK_THROW(rectangle.scale(-3.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(correctMoveCircle)
{
  biryukova::Circle circle(biryukova::point_t{1.8, 4.2}, 8.1);
  const double dx = 1.0;
  const double dy = 2.0;
  const double x = circle.getCentre().x;
  const double y = circle.getCentre().y;
  circle.move(dx, dy);
  BOOST_CHECK_CLOSE(circle.getCentre().x, x + dx, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle.getCentre().y, y + dy, ACCURACY_DOUBLE);
  circle.move({x, y});
  BOOST_CHECK_CLOSE(circle.getCentre().x, x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle.getCentre().y, y, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(correctMoveRectangle)
{
  biryukova::Rectangle rectangle(biryukova::point_t{3.0, 7.1}, 9.4, 2.4);
  const double dx = 1.0;
  const double dy = 2.0;
  const double x = rectangle.getCentre().x;
  const double y = rectangle.getCentre().y;
  rectangle.move(dx, dy);
  BOOST_CHECK_CLOSE(rectangle.getCentre().x, x + dx, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rectangle.getCentre().y, y + dy, ACCURACY_DOUBLE);
  rectangle.move({x, y});
  BOOST_CHECK_CLOSE(rectangle.getCentre().x, x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rectangle.getCentre().y, y, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(correctGetFrameRectCircle)
{
  biryukova::Circle circle(biryukova::point_t{1.8, 4.2}, 1.0);
  biryukova::rectangle_t frameRect = circle.getFrameRect();
  const double x = circle.getCentre().x;
  const double y = circle.getCentre().y;
  const double height = circle.getRadius() * 2;
  const double width = circle.getRadius() * 2;
  BOOST_CHECK_CLOSE(frameRect.pos.x, x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.pos.y, y, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.height, height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.width, width, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(correctGetFrameRectRectangle)
{
  biryukova::Rectangle rectangle(biryukova::point_t{3.0, 7.1}, 9.4, 2.4);
  biryukova::rectangle_t frameRect = rectangle.getFrameRect();
  BOOST_CHECK_CLOSE(rectangle.getCentre().x, frameRect.pos.x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rectangle.getCentre().y, frameRect.pos.y, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rectangle.getHeight(), frameRect.height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rectangle.getWidth(), frameRect.width, ACCURACY_DOUBLE);
}
