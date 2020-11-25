#define BOOST_TEST_MODULE MYTEST

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"

const double TOLERANCE_RANGE = 0.00001;

BOOST_AUTO_TEST_CASE(test_invalid_radius_circle)
{
  BOOST_CHECK_THROW(vasilevskaya::Circle circle({ 0.0, 0.0 }, -1.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_coefficient_scaling_circle)
{
  vasilevskaya::Circle circle({ 0.0, 0.0 }, 1.0);
  BOOST_CHECK_THROW(circle.scale(-2.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_width_rectangle)
{
  BOOST_CHECK_THROW(vasilevskaya::Rectangle myRectangle(-2.5, 7.8, { -2.3, 6.0 }), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_height_rectangle)
{
  BOOST_CHECK_THROW(vasilevskaya::Rectangle myRectangle(2.5, -7.8, { -2.3, 6.0 }), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_coefficient_scaling_rectangle)
{
  vasilevskaya::Rectangle myRectangle(2.5, 7.8, { -2.3, 6.0 });
  BOOST_CHECK_THROW(myRectangle.scale(-4.25), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_triangle)
{
  BOOST_CHECK_THROW(vasilevskaya::Triangle myTriangle({ 1.0, 1.0 }, { 2.0, 2.0 }, { 3.0, 3.0 }), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_scale_triangle)
{
  vasilevskaya::Triangle myTriangle({ 0.0, 1.0 }, { 3.0, 1.0 }, { 4.0, 0.0 });
  BOOST_CHECK_THROW(myTriangle.scale(-2.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_immutability_circle_moving)
{
  vasilevskaya::Circle myCircle({ 5, 4 }, 1.5);
  vasilevskaya::rectangle_t frameRect = myCircle.getFrameRect();
  const double area = myCircle.getArea();

  myCircle.move({ 3.7, 10.0 });
  BOOST_CHECK_CLOSE(frameRect.width, myCircle.getFrameRect().width, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.height, myCircle.getFrameRect().height, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(area, myCircle.getArea(), TOLERANCE_RANGE);

  myCircle.move(9.4, 2.6);
  BOOST_CHECK_CLOSE(frameRect.width, myCircle.getFrameRect().width, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.height, myCircle.getFrameRect().height, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(area, myCircle.getArea(), TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_immutability_rectangle_moving)
{
  vasilevskaya::Rectangle myRectangle(6.4, 3.0, { 3.8, 8.0 });
  vasilevskaya::rectangle_t frameRect = myRectangle.getFrameRect();
  const double area = myRectangle.getArea();

  myRectangle.move({ 3.8, 10.0 });
  BOOST_CHECK_CLOSE(frameRect.width, myRectangle.getFrameRect().width, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.height, myRectangle.getFrameRect().height, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(area, myRectangle.getArea(), TOLERANCE_RANGE);

  myRectangle.move(5.0, 2.0);
  BOOST_CHECK_CLOSE(frameRect.width, myRectangle.getFrameRect().width, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.height, myRectangle.getFrameRect().height, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(area, myRectangle.getArea(), TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_immutability_triangle_moving)
{
  vasilevskaya::Triangle myTriangle({ 0.0, 0.0 }, { 0.0, 3.0 }, { 4.0, 0.0 });
  vasilevskaya::rectangle_t frameRect = myTriangle.getFrameRect();
  const double area = myTriangle.getArea();

  myTriangle.move({ 1.0, 1.0 });
  BOOST_CHECK_CLOSE(frameRect.width, myTriangle.getFrameRect().width, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.height, myTriangle.getFrameRect().height, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(area, myTriangle.getArea(), TOLERANCE_RANGE);

  myTriangle.move(2.0, -3.0);
  BOOST_CHECK_CLOSE(frameRect.width, myTriangle.getFrameRect().width, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRect.height, myTriangle.getFrameRect().height, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(area, myTriangle.getArea(), TOLERANCE_RANGE);
}


BOOST_AUTO_TEST_CASE(test_circle_scaling)
{
  vasilevskaya::Circle myCircle({ 4.6, -5.0 }, 5.5);
  const double area = myCircle.getArea();
  const double coefficient = 2.0;
  myCircle.scale(coefficient);
  BOOST_CHECK_CLOSE(area * coefficient * coefficient, myCircle.getArea(), TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_rectangle_scaling)
{
  vasilevskaya::Rectangle myRectangle(7.9, 6.0, { -2.0, 4.3 });
  const double area = myRectangle.getArea();
  const double coefficient = 2.0;
  myRectangle.scale(coefficient);
  BOOST_CHECK_CLOSE(area * coefficient * coefficient, myRectangle.getArea(), TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_triangle_scaling)
{
  vasilevskaya::Triangle myTriangle({ 0.0, 0.0 }, { 0.0, 3.0 }, { 4.0, 0.0 });
  const double area = myTriangle.getArea();
  const double coefficient = 2.0;
  myTriangle.scale(coefficient);
  BOOST_CHECK_CLOSE(area * coefficient * coefficient, myTriangle.getArea(), TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_CompositeShape_add)
{
  vasilevskaya::CompositeShape shapes;
  std::shared_ptr<vasilevskaya::Shape> shape = nullptr;

  BOOST_CHECK_THROW(shapes.pushBack(shape), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_CompositeShape_remove)
{
  vasilevskaya::CompositeShape shapes;

  BOOST_CHECK_THROW(shapes.remove(1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_index_CompositeShape)
{
  vasilevskaya::CompositeShape shapes;

  BOOST_CHECK_THROW(shapes[1], std::out_of_range);

  std::shared_ptr<vasilevskaya::Shape> circle =
    std::make_shared<vasilevskaya::Circle>(vasilevskaya::point_t{ 1.8, 4.2 }, 8.1);

  shapes.pushBack(circle);

  BOOST_CHECK_THROW(shapes[1], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_parameter_CompositeShape_scale)
{
  vasilevskaya::CompositeShape shapes;

  std::shared_ptr<vasilevskaya::Shape> circle =
    std::make_shared<vasilevskaya::Circle>(vasilevskaya::point_t{ 1.8, 4.2 }, 8.1);

  shapes.pushBack(circle);

  BOOST_CHECK_THROW(shapes.scale(-1.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_scale_CompositeShape)
{
  std::shared_ptr<vasilevskaya::Shape> rect
    = std::make_shared<vasilevskaya::Rectangle>(11.0, 10.0, vasilevskaya::point_t{ 1.0, 1.0 });

  std::shared_ptr<vasilevskaya::Shape> circle = std::make_shared<vasilevskaya::Circle>(vasilevskaya::Circle({ 10.0, 10.0 }, 10.0));

  vasilevskaya::CompositeShape array;

  array.pushBack(circle);
  array.pushBack(rect);

  const double AREA_RECT = rect->getArea();
  const double COEFFICIENT = 2.0;
  const double AREA_CIRCLE = circle->getArea();

  array.scale(COEFFICIENT);

  BOOST_CHECK_CLOSE(AREA_CIRCLE * COEFFICIENT * COEFFICIENT, circle->getArea(), TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(AREA_RECT * COEFFICIENT * COEFFICIENT, rect->getArea(), TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_CompositeShape_getSize)
{
  vasilevskaya::CompositeShape shapes;

  std::shared_ptr<vasilevskaya::Shape> circle =
    std::make_shared<vasilevskaya::Circle>(vasilevskaya::point_t{ 1.8, 4.2 }, 8.1);

  std::shared_ptr<vasilevskaya::Shape> rectangle =
    std::make_shared<vasilevskaya::Rectangle>(9.4, 2.4, vasilevskaya::point_t{ 3.0, 7.1 });

  shapes.pushBack(rectangle);

  shapes.pushBack(circle);

  BOOST_CHECK(shapes.getCount() == 2);
}

BOOST_AUTO_TEST_CASE(test_CompositeShape_getArea)
{
  vasilevskaya::CompositeShape shapes;

  std::shared_ptr<vasilevskaya::Shape> circle =
    std::make_shared<vasilevskaya::Circle>(vasilevskaya::point_t{ 1.8, 4.2 }, 8.1);

  std::shared_ptr<vasilevskaya::Shape> rectangle =
    std::make_shared<vasilevskaya::Rectangle>(9.4, 2.4, vasilevskaya::point_t{ 3.0, 7.1 });

  const double area = circle->getArea() + rectangle->getArea();

  shapes.pushBack(rectangle);
  shapes.pushBack(circle);

  BOOST_CHECK(shapes.getArea() == area);
}

BOOST_AUTO_TEST_CASE(test_constancy_parameters_AfterMove_CompositeShape)
{
  vasilevskaya::Circle circle(vasilevskaya::point_t{ 1.8, 4.2 }, 8.1);

  std::shared_ptr<vasilevskaya::Shape> shape1 =
    std::make_shared<vasilevskaya::Circle>(circle);

  const double areaCircle = circle.getArea();
  const double radiusCircle = circle.getRadius();

  vasilevskaya::Rectangle rectangle(9.4, 2.4, vasilevskaya::point_t{ 3.0, 7.1 });

  std::shared_ptr<vasilevskaya::Shape> shape2 =
    std::make_shared<vasilevskaya::Rectangle>(rectangle);

  const double areaRectangle = rectangle.getArea();
  const double heightRectangle = rectangle.getHeight();
  const double widthRectangle = rectangle.getWidth();

  vasilevskaya::CompositeShape shapes;

  shapes.pushBack(shape1);
  shapes.pushBack(shape2);

  shapes.move(vasilevskaya::point_t{ 3.9, 7.2 });

  BOOST_CHECK_CLOSE(areaRectangle, shapes[1]->getArea(), TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(heightRectangle, shapes[1]->getFrameRect().height, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(widthRectangle, shapes[1]->getFrameRect().width, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(areaCircle, shapes[0]->getArea(), TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(radiusCircle * 2, shapes[0]->getFrameRect().height, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(radiusCircle * 2, shapes[0]->getFrameRect().width, TOLERANCE_RANGE);

  shapes.move(1.0, 2.0);

  BOOST_CHECK_CLOSE(areaRectangle, shapes[1]->getArea(), TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(heightRectangle, shapes[1]->getFrameRect().height, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(widthRectangle, shapes[1]->getFrameRect().width, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(areaCircle, shapes[0]->getArea(), TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(radiusCircle * 2, shapes[0]->getFrameRect().height, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(radiusCircle * 2, shapes[0]->getFrameRect().width, TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_CompositeShape_getFrameRect)
{
  std::shared_ptr<vasilevskaya::Shape> circle =
    std::make_shared<vasilevskaya::Circle>(vasilevskaya::point_t{ 1.0, 1.0 }, 1.0);

  std::shared_ptr<vasilevskaya::Shape> rectangle =
    std::make_shared<vasilevskaya::Rectangle>(1.0, 1.0, vasilevskaya::point_t{ 1.0, 1.0 });

  const double frameHeight = 2.0;
  const double frameWidth = 2.0;

  const vasilevskaya::point_t framePos = { 1.0, 1.0 };

  vasilevskaya::CompositeShape shapes;

  shapes.pushBack(rectangle);
  shapes.pushBack(circle);

  vasilevskaya::Rectangle frameRectangle(shapes.getFrameRect().width, shapes.getFrameRect().height, shapes.getFrameRect().pos);

  BOOST_CHECK_CLOSE(frameRectangle.getHeight(), frameHeight, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(frameRectangle.getWidth(), frameWidth, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(framePos.x, frameRectangle.getPosition().x, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(framePos.y, frameRectangle.getPosition().y, TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_correct_move_CompositeShape)
{
  const double X = 1.8;
  const double Y = 3.0;

  std::shared_ptr<vasilevskaya::Shape> circle =
    std::make_shared<vasilevskaya::Circle>(vasilevskaya::point_t{ X, Y }, 1.0);

  std::shared_ptr<vasilevskaya::Shape> rectangle =
    std::make_shared<vasilevskaya::Rectangle>(9.4, 2.4, vasilevskaya::point_t{ X, Y });

  const double DIFF_X = 1.0;
  const double DIFF_Y = 2.0;

  vasilevskaya::CompositeShape shapes;

  shapes.pushBack(rectangle);
  shapes.pushBack(circle);

  shapes.move(DIFF_X, DIFF_Y);
  BOOST_CHECK_CLOSE(shapes[0]->getFrameRect().pos.x, X + DIFF_X, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(shapes[0]->getFrameRect().pos.y, Y + DIFF_Y, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(shapes[1]->getFrameRect().pos.x, X + DIFF_X, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(shapes[1]->getFrameRect().pos.y, Y + DIFF_Y, TOLERANCE_RANGE);

  shapes.move({ X, Y });
  BOOST_CHECK_CLOSE(shapes[0]->getFrameRect().pos.x, X, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(shapes[0]->getFrameRect().pos.y, Y, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(shapes[1]->getFrameRect().pos.x, X, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(shapes[1]->getFrameRect().pos.y, Y, TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_copying_CompositeShape)
{
  std::shared_ptr<vasilevskaya::Shape> shape =
    std::make_shared<vasilevskaya::Circle>(vasilevskaya::point_t{ 1.8, 4.2 }, 8.1);

  vasilevskaya::CompositeShape shapes1;

  shapes1.pushBack(shape);

  vasilevskaya::CompositeShape shapes2(shapes1);

  BOOST_CHECK_CLOSE(shapes1[0]->getPosition().x, shapes2[0]->getPosition().x, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(shapes1[0]->getPosition().y, shapes2[0]->getPosition().y, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(shapes1[0]->getArea(), shapes2[0]->getArea(), TOLERANCE_RANGE);

  vasilevskaya::CompositeShape shapes3;
  shapes3 = shapes2;

  BOOST_CHECK_CLOSE(shapes3[0]->getPosition().x, shapes2[0]->getPosition().x, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(shapes3[0]->getPosition().y, shapes2[0]->getPosition().y, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(shapes3[0]->getArea(), shapes2[0]->getArea(), TOLERANCE_RANGE);
}

BOOST_AUTO_TEST_CASE(test_moving_CompositeShape)
{
  std::shared_ptr<vasilevskaya::Shape> shape =
    std::make_shared<vasilevskaya::Circle>(vasilevskaya::point_t{ 1.8, 4.2 }, 8.1);

  const double SHAPE_AREA = shape->getArea();
  const double SHAPE_CENTER_X = shape->getPosition().x;
  const double SHAPE_CENTER_Y = shape->getPosition().y;

  vasilevskaya::CompositeShape shapes1;

  shapes1.pushBack(shape);

  vasilevskaya::CompositeShape shapes2(std::move(shapes1));

  BOOST_CHECK_CLOSE(SHAPE_CENTER_X, shapes2[0]->getPosition().x, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(SHAPE_CENTER_Y, shapes2[0]->getPosition().y, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(SHAPE_AREA, shapes2[0]->getArea(), TOLERANCE_RANGE);

  vasilevskaya::CompositeShape shapes3;

  shapes3 = std::move(shapes2);

  BOOST_CHECK_CLOSE(SHAPE_CENTER_X, shapes3[0]->getPosition().x, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(SHAPE_CENTER_Y, shapes3[0]->getPosition().y, TOLERANCE_RANGE);
  BOOST_CHECK_CLOSE(SHAPE_AREA, shapes3[0]->getArea(), TOLERANCE_RANGE);
}

