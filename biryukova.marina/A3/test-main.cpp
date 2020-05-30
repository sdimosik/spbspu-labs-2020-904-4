#define BOOST_TEST_MODULE TEST_A3
#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double ACCURACY_DOUBLE = 0.00001;

BOOST_AUTO_TEST_CASE(invalidParameterInsertCompositeShape)
{
  biryukova::CompositeShape shapes;
  biryukova::CompositeShape::shapePtr shape = nullptr;
  BOOST_CHECK_THROW(shapes.insert(shape), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalidParameterRemoveCompositeShape)
{
  biryukova::CompositeShape shapes;
  BOOST_CHECK_THROW(shapes.remove(1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(invalidIndexCompositeShape)
{
  biryukova::CompositeShape shapes;
  BOOST_CHECK_THROW(shapes[1], std::out_of_range);
  biryukova::CompositeShape::shapePtr circle = 
      std::make_shared<biryukova::Circle>(biryukova::point_t{1.8, 4.2}, 8.1);
  shapes.insert(circle);
  BOOST_CHECK_THROW(shapes[1], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(invalidParameterScaleCompositeShape)
{
  biryukova::CompositeShape shapes;
  biryukova::CompositeShape::shapePtr circle = 
      std::make_shared<biryukova::Circle>(biryukova::point_t{1.8, 4.2}, 8.1);
  shapes.insert(circle);
  BOOST_CHECK_THROW(shapes.scale(-1.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(afterScaleCompositeShape)
{
  double coefficient = 3.0;
  biryukova::CompositeShape::shapePtr rectangle =
      std::make_shared<biryukova::Rectangle>(biryukova::point_t{1.0, 1.0}, 1.0, 1.0);
  double areaRectangle = rectangle->getArea() * coefficient * coefficient;
  biryukova::CompositeShape::shapePtr circle =
      std::make_shared<biryukova::Circle>(biryukova::point_t{2.0, 2.0}, 1.0);
  double areaCircle = circle->getArea() * coefficient * coefficient;
  biryukova::CompositeShape shapes;
  shapes.insert(rectangle);
  shapes.insert(circle);
  biryukova::point_t centerOfShapes = shapes.getCentre();
  double distanceToCentreRecX = centerOfShapes.x - rectangle->getCentre().x;
  double distanceToCentreRecY = centerOfShapes.y - rectangle->getCentre().y;
  double distanceToCentreCircleX = centerOfShapes.x - circle->getCentre().x;
  double distanceToCentreCircleY = centerOfShapes.y - circle->getCentre().y;
  shapes.scale(coefficient);
  BOOST_CHECK_CLOSE(areaRectangle, shapes[0]->getArea(), ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(areaCircle, shapes[1]->getArea(), ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(distanceToCentreRecX * coefficient,
      centerOfShapes.x - rectangle->getCentre().x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(distanceToCentreRecY * coefficient,
      centerOfShapes.y - rectangle->getCentre().y, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(distanceToCentreCircleX * coefficient,
      centerOfShapes.x - circle->getCentre().x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(distanceToCentreCircleY * coefficient,
      centerOfShapes.y - circle->getCentre().y, ACCURACY_DOUBLE);
  coefficient = 0.5;
  areaRectangle = rectangle->getArea() * coefficient * coefficient;
  areaCircle = circle->getArea() * coefficient * coefficient;
  distanceToCentreRecX = centerOfShapes.x - rectangle->getCentre().x;
  distanceToCentreRecY = centerOfShapes.y - rectangle->getCentre().y;
  distanceToCentreCircleX = centerOfShapes.x - circle->getCentre().x;
  distanceToCentreCircleY = centerOfShapes.y - circle->getCentre().y;
  shapes.scale(coefficient);
  BOOST_CHECK_CLOSE(areaRectangle, shapes[0]->getArea(), ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(areaCircle, shapes[1]->getArea(), ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(distanceToCentreRecX * coefficient,
      centerOfShapes.x - rectangle->getCentre().x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(distanceToCentreRecY * coefficient,
      centerOfShapes.y - rectangle->getCentre().y, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(distanceToCentreCircleX * coefficient,
      centerOfShapes.x - circle->getCentre().x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(distanceToCentreCircleY * coefficient,
      centerOfShapes.y - circle->getCentre().y, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(testGetSizeCompositeShape)
{
  biryukova::CompositeShape shapes;
  biryukova::CompositeShape::shapePtr circle =
      std::make_shared<biryukova::Circle>(biryukova::point_t{1.8, 4.2}, 8.1);
  biryukova::CompositeShape::shapePtr rectangle =
      std::make_shared<biryukova::Rectangle>(biryukova::point_t{3.0, 7.1}, 9.4, 2.4);
  shapes.insert(rectangle);
  shapes.insert(circle);
  BOOST_CHECK(shapes.getSize() == 2);
}

BOOST_AUTO_TEST_CASE(testGetAreaCompositeShape)
{
  biryukova::CompositeShape shapes;
  biryukova::CompositeShape::shapePtr circle =
      std::make_shared<biryukova::Circle>(biryukova::point_t{1.8, 4.2}, 8.1);
  biryukova::CompositeShape::shapePtr rectangle =
      std::make_shared<biryukova::Rectangle>(biryukova::point_t{3.0, 7.1}, 9.4, 2.4);
  const double area = circle->getArea() + rectangle->getArea();
  shapes.insert(rectangle);
  shapes.insert(circle);
  BOOST_CHECK(shapes.getArea() == area);
}

BOOST_AUTO_TEST_CASE(constancyParametersAfterMoveCompositeShape)
{
  biryukova::Circle circle(biryukova::point_t{1.8, 4.2}, 8.1);
  biryukova::CompositeShape::shapePtr shape1 =
      std::make_shared<biryukova::Circle>(circle);
  const double areaCircle = circle.getArea();
  const double radiusCircle = circle.getRadius();
  biryukova::Rectangle rectangle(biryukova::point_t{3.0, 7.1}, 9.4, 2.4);
  biryukova::CompositeShape::shapePtr shape2 =
      std::make_shared<biryukova::Rectangle>(rectangle);
  const double areaRectangle = rectangle.getArea();
  const double heightRectangle = rectangle.getHeight();
  const double widthRectangle = rectangle.getWidth();
  biryukova::CompositeShape shapes;
  shapes.insert(shape1);
  shapes.insert(shape2);
  shapes.move(biryukova::point_t{3.9, 7.2});
  BOOST_CHECK_CLOSE(areaRectangle, shapes[1]->getArea(), ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(heightRectangle, shapes[1]->getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(widthRectangle, shapes[1]->getFrameRect().width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(areaCircle, shapes[0]->getArea(), ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(radiusCircle * 2, shapes[0]->getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(radiusCircle * 2, shapes[0]->getFrameRect().width, ACCURACY_DOUBLE);
  shapes.move(1.0, 2.0);
  BOOST_CHECK_CLOSE(areaRectangle, shapes[1]->getArea(), ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(heightRectangle, shapes[1]->getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(widthRectangle, shapes[1]->getFrameRect().width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(areaCircle, shapes[0]->getArea(), ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(radiusCircle * 2, shapes[0]->getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(radiusCircle * 2, shapes[0]->getFrameRect().width, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(testGetFrameRectCompositeShape)
{
  biryukova::CompositeShape::shapePtr circle =
      std::make_shared<biryukova::Circle>(biryukova::point_t{1.0, 1.0}, 1.0);
  biryukova::CompositeShape::shapePtr rectangle =
      std::make_shared<biryukova::Rectangle>(biryukova::point_t{1.0, 1.0}, 1.0, 1.0);
  const double frameHeight = 2.0;
  const double frameWidth = 2.0;
  const biryukova::point_t framePos = {1.0, 1.0};
  biryukova::CompositeShape shapes;
  shapes.insert(rectangle);
  shapes.insert(circle);
  biryukova::Rectangle frameRectangle = shapes.getFrameRect();
  BOOST_CHECK_CLOSE(frameRectangle.getHeight(), frameHeight, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRectangle.getWidth(), frameWidth, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(framePos.x, frameRectangle.getCentre().x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(framePos.y, frameRectangle.getCentre().y, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(correctMoveCompositeShape)
{
  const double x = 1.8;
  const double y = 3.0;
  biryukova::CompositeShape::shapePtr circle =
      std::make_shared<biryukova::Circle>(biryukova::point_t{x, y}, 1.0);
  biryukova::CompositeShape::shapePtr rectangle =
      std::make_shared<biryukova::Rectangle>(biryukova::point_t{x, y}, 9.4, 2.4);
  const double dx = 1.0;
  const double dy = 2.0;
  biryukova::CompositeShape shapes;
  shapes.insert(rectangle);
  shapes.insert(circle);
  shapes.move(dx, dy);
  BOOST_CHECK_CLOSE(shapes[0]->getFrameRect().pos.x, x + dx, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(shapes[0]->getFrameRect().pos.y, y + dy, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(shapes[1]->getFrameRect().pos.x, x + dx, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(shapes[1]->getFrameRect().pos.y, y + dy, ACCURACY_DOUBLE);
  shapes.move({x, y});
  BOOST_CHECK_CLOSE(shapes[0]->getFrameRect().pos.x, x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(shapes[0]->getFrameRect().pos.y, y, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(shapes[1]->getFrameRect().pos.x, x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(shapes[1]->getFrameRect().pos.y, y, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(testOfCopyingCompositeShape)
{
  biryukova::CompositeShape::shapePtr shape =
      std::make_shared<biryukova::Circle>(biryukova::point_t{1.8, 4.2}, 8.1);
  biryukova::CompositeShape shapes1;
  shapes1.insert(shape);
  biryukova::CompositeShape shapes2(shapes1);
  BOOST_CHECK_CLOSE(shapes1[0]->getCentre().x, shapes2[0]->getCentre().x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(shapes1[0]->getCentre().y, shapes2[0]->getCentre().y, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(shapes1[0]->getArea(), shapes2[0]->getArea(), ACCURACY_DOUBLE);
  biryukova::CompositeShape shapes3;
  shapes3 = shapes2;
  BOOST_CHECK_CLOSE(shapes3[0]->getCentre().x, shapes2[0]->getCentre().x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(shapes3[0]->getCentre().y, shapes2[0]->getCentre().y, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(shapes3[0]->getArea(), shapes2[0]->getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(testOfMovingCompositeShape)
{
  biryukova::CompositeShape::shapePtr shape =
      std::make_shared<biryukova::Circle>(biryukova::point_t{ 1.8, 4.2 }, 8.1);
  const double areaShape = shape->getArea();
  const double centreShapeX = shape->getCentre().x;
  const double centreShapeY = shape->getCentre().y;
  biryukova::CompositeShape shapes1;
  shapes1.insert(shape);
  biryukova::CompositeShape shapes2(std::move(shapes1));
  BOOST_CHECK_CLOSE(centreShapeX, shapes2[0]->getCentre().x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(centreShapeY, shapes2[0]->getCentre().y, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(areaShape, shapes2[0]->getArea(), ACCURACY_DOUBLE);
  biryukova::CompositeShape shapes3;
  shapes3 = std::move(shapes2);
  BOOST_CHECK_CLOSE(centreShapeX, shapes3[0]->getCentre().x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(centreShapeY, shapes3[0]->getCentre().y, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(areaShape, shapes3[0]->getArea(), ACCURACY_DOUBLE);
}
