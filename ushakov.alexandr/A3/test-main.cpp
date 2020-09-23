#define BOOST_TEST_MODULE A1_TEST

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"

const double ACCURACY = 0.00001;

BOOST_AUTO_TEST_CASE(test_invalid_argument_circle)
{
  BOOST_CHECK_THROW(ushakov::Circle circle({0.0, 0.0}, -1.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_width_rectangle)
{
  BOOST_CHECK_THROW(ushakov::Rectangle rectangle(-1.0, 2.0, {0.0, 0.0}), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_height_rectangle)
{
  BOOST_CHECK_THROW(ushakov::Rectangle rectangle(1.0, -2.0, {0.0, 0.0}), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_triangle)
{
  BOOST_CHECK_THROW(ushakov::Triangle triangle({1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_scale_circle)
{
  ushakov::Circle circle({0.0, 0.0}, 1);

  BOOST_CHECK_THROW(circle.scale(-2.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_scale_rectangle)
{
  ushakov::Rectangle rectangle(1.0, 3.0, {0.0, 0.0});

  BOOST_CHECK_THROW(rectangle.scale(-2.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_scale_triangle)
{
  ushakov::Triangle triangle({0.0, 0.0}, {0.0, 3.0}, {4.0, 0.0});

  BOOST_CHECK_THROW(triangle.scale(-2.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_scale_area_circle)
{
  ushakov::Circle circle({0.0, 0.0}, 1.0);

  const double CIRCLE_AREA = circle.getArea();
  const double COEFFICIENT = 2.0;

  circle.scale(COEFFICIENT);

  BOOST_CHECK_CLOSE(CIRCLE_AREA * COEFFICIENT * COEFFICIENT, circle.getArea(), ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_scale_area_rectangle)
{
  ushakov::Rectangle rectangle(1.0, 3.0, {0.0, 0.0});

  const double RECTANGLE_AREA = rectangle.getArea();
  const double COEFFICIENT = 2.0;

  rectangle.scale(COEFFICIENT);

  BOOST_CHECK_CLOSE(RECTANGLE_AREA * COEFFICIENT * COEFFICIENT, rectangle.getArea(), ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_scale_area_triangle)
{
  ushakov::Triangle triangle({0.0, 0.0}, {0.0, 3.0}, {4.0, 0.0});

  const double TRIANGLE_AREA = triangle.getArea();
  const double COEFFICIENT = 2.0;

  triangle.scale(COEFFICIENT);

  BOOST_CHECK_CLOSE(TRIANGLE_AREA * COEFFICIENT * COEFFICIENT, triangle.getArea(), ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_move_constancy_circle)
{
  ushakov::Circle circle({0.0, 0.0}, 1.0);
  ushakov::rectangle_t circleFrame = circle.getFrameRect();

  const double CIRCLE_AREA = circle.getArea();

  circle.move(2.0, -3.0);

  BOOST_CHECK_CLOSE(circleFrame.width, circle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(circleFrame.height, circle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(CIRCLE_AREA, circle.getArea(), ACCURACY);

  circle.move({1.0, 1.0});

  BOOST_CHECK_CLOSE(circleFrame.width, circle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(circleFrame.height, circle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(CIRCLE_AREA, circle.getArea(), ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_move_constancy_rectangle)
{
  ushakov::Rectangle rectangle(2.0, 5.0, {0.0, 0.0});
  ushakov::rectangle_t rectangleFrame = rectangle.getFrameRect();

  const double rectangleArea = rectangle.getArea();

  rectangle.move(2.0, -3.0);

  BOOST_CHECK_CLOSE(rectangleFrame.width, rectangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(rectangleFrame.height, rectangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(rectangleArea, rectangle.getArea(), ACCURACY);

  rectangle.move({1.0, 1.0});

  BOOST_CHECK_CLOSE(rectangleFrame.width, rectangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(rectangleFrame.height, rectangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(rectangleArea, rectangle.getArea(), ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_move_constancy_triangle)
{
  ushakov::Triangle triangle({0.0, 0.0}, {0.0, 3.0}, {4.0, 0.0});
  ushakov::rectangle_t triangleFrame = triangle.getFrameRect();

  const double TRIANGLE_AREA = triangle.getArea();

  triangle.move(2.0, -3.0);

  BOOST_CHECK_CLOSE(triangleFrame.width, triangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(triangleFrame.height, triangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(TRIANGLE_AREA, triangle.getArea(), ACCURACY);

  triangle.move({1.0, 1.0});

  BOOST_CHECK_CLOSE(triangleFrame.width, triangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(triangleFrame.height, triangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(TRIANGLE_AREA, triangle.getArea(), ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_correct_move_circle)
{
  ushakov::Circle circle({0.0, 0.0}, 1.0);

  const double DIFF_X = 3.0;
  const double DIFF_Y = 4.0;
  const double X = circle.getPosition().x;
  const double Y = circle.getPosition().y;

  circle.move(DIFF_X, DIFF_Y);

  BOOST_CHECK_CLOSE(circle.getPosition().x, DIFF_X + X, ACCURACY);
  BOOST_CHECK_CLOSE(circle.getPosition().y, DIFF_Y + Y, ACCURACY);

  circle.move({DIFF_X, DIFF_Y});

  BOOST_CHECK_CLOSE(circle.getPosition().x, DIFF_X, ACCURACY);
  BOOST_CHECK_CLOSE(circle.getPosition().y, DIFF_Y, ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_correct_move_rectangle)
{
  ushakov::Rectangle rectangle(1.0, 3.0, {0.0, 0.0});

  const double DIFF_X = 3.0;
  const double DIFF_Y = 4.0;
  const double X = rectangle.getPosition().x;
  const double Y = rectangle.getPosition().y;

  rectangle.move(DIFF_X, DIFF_Y);

  BOOST_CHECK_CLOSE(rectangle.getPosition().x, DIFF_X + X, ACCURACY);
  BOOST_CHECK_CLOSE(rectangle.getPosition().y, DIFF_Y + Y, ACCURACY);

  rectangle.move({DIFF_X, DIFF_Y});

  BOOST_CHECK_CLOSE(rectangle.getPosition().x, DIFF_X, ACCURACY);
  BOOST_CHECK_CLOSE(rectangle.getPosition().y, DIFF_Y, ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_correct_move_triangle)
{
  ushakov::Triangle triangle({0.0, 0.0}, {0.0, 3.0}, {4.0, 0.0});

  const double DIFF_X = 3.0;
  const double DIFF_Y = 4.0;
  const double X = triangle.getPosition().x;
  const double Y = triangle.getPosition().y;

  triangle.move(DIFF_X, DIFF_Y);

  BOOST_CHECK_CLOSE(triangle.getPosition().x, DIFF_X + X, ACCURACY);
  BOOST_CHECK_CLOSE(triangle.getPosition().y, DIFF_Y + Y, ACCURACY);

  triangle.move({DIFF_X, DIFF_Y});

  BOOST_CHECK_CLOSE(triangle.getPosition().x, DIFF_X, ACCURACY);
  BOOST_CHECK_CLOSE(triangle.getPosition().y, DIFF_Y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_CompositeShape_add)
{
  ushakov::CompositeShape shapes;
  std::shared_ptr<ushakov::Shape> shape = nullptr;

  BOOST_CHECK_THROW(shapes.addShape(shape), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_CompositeShape_remove)
{
  ushakov::CompositeShape shapes;

  BOOST_CHECK_THROW(shapes.removeShape(1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_index_CompositeShape)
{
  ushakov::CompositeShape shapes;

  BOOST_CHECK_THROW(shapes[1], std::out_of_range);

  std::shared_ptr<ushakov::Shape> circle =
      std::make_shared<ushakov::Circle>(ushakov::point_t{1.8, 4.2}, 8.1);

  shapes.addShape(circle);

  BOOST_CHECK_THROW(shapes[1], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_parameter_CompositeShape_scale)
{
  ushakov::CompositeShape shapes;

  std::shared_ptr<ushakov::Shape> circle =
      std::make_shared<ushakov::Circle>(ushakov::point_t{1.8, 4.2}, 8.1);

  shapes.addShape(circle);

  BOOST_CHECK_THROW(shapes.scale(-1.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_scale_CompositeShape)
{
  std::shared_ptr<ushakov::Shape> rect
      = std::make_shared<ushakov::Rectangle>(11.0, 10.0, ushakov::point_t{1.0, 1.0});

  std::shared_ptr<ushakov::Shape> circle = std::make_shared<ushakov::Circle>(ushakov::Circle({10.0, 10.0}, 10.0));

  ushakov::CompositeShape array;

  array.addShape(circle);
  array.addShape(rect);

  const double AREA_RECT = rect->getArea();
  const double COEFFICIENT = 2.0;
  const double AREA_CIRCLE = circle->getArea();

  array.scale(COEFFICIENT);

  BOOST_CHECK_CLOSE(AREA_CIRCLE * COEFFICIENT * COEFFICIENT, circle->getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(AREA_RECT * COEFFICIENT * COEFFICIENT, rect->getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_CompositeShape_getSize)
{
  ushakov::CompositeShape shapes;

  std::shared_ptr<ushakov::Shape> circle =
      std::make_shared<ushakov::Circle>(ushakov::point_t{1.8, 4.2}, 8.1);

  std::shared_ptr<ushakov::Shape> rectangle =
      std::make_shared<ushakov::Rectangle>(9.4, 2.4, ushakov::point_t{3.0, 7.1});

  shapes.addShape(rectangle);

  shapes.addShape(circle);

  BOOST_CHECK(shapes.getSize() == 2);
}

BOOST_AUTO_TEST_CASE(test_CompositeShape_getArea)
{
  ushakov::CompositeShape shapes;

  std::shared_ptr<ushakov::Shape> circle =
      std::make_shared<ushakov::Circle>(ushakov::point_t{1.8, 4.2}, 8.1);

  std::shared_ptr<ushakov::Shape> rectangle =
      std::make_shared<ushakov::Rectangle>(9.4, 2.4, ushakov::point_t{3.0, 7.1});

  const double area = circle->getArea() + rectangle->getArea();

  shapes.addShape(rectangle);
  shapes.addShape(circle);

  BOOST_CHECK(shapes.getArea() == area);
}

BOOST_AUTO_TEST_CASE(test_constancy_parameters_AfterMove_CompositeShape)
{
  ushakov::Circle circle(ushakov::point_t{1.8, 4.2}, 8.1);

  std::shared_ptr<ushakov::Shape> shape1 =
      std::make_shared<ushakov::Circle>(circle);

  const double areaCircle = circle.getArea();
  const double radiusCircle = circle.getRadius();

  ushakov::Rectangle rectangle(9.4, 2.4, ushakov::point_t{3.0, 7.1});

  std::shared_ptr<ushakov::Shape> shape2 =
      std::make_shared<ushakov::Rectangle>(rectangle);

  const double areaRectangle = rectangle.getArea();
  const double heightRectangle = rectangle.getHeight();
  const double widthRectangle = rectangle.getWidth();

  ushakov::CompositeShape shapes;

  shapes.addShape(shape1);
  shapes.addShape(shape2);

  shapes.move(ushakov::point_t{3.9, 7.2});

  BOOST_CHECK_CLOSE(areaRectangle, shapes[1]->getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(heightRectangle, shapes[1]->getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(widthRectangle, shapes[1]->getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(areaCircle, shapes[0]->getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(radiusCircle * 2, shapes[0]->getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(radiusCircle * 2, shapes[0]->getFrameRect().width, ACCURACY);

  shapes.move(1.0, 2.0);

  BOOST_CHECK_CLOSE(areaRectangle, shapes[1]->getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(heightRectangle, shapes[1]->getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(widthRectangle, shapes[1]->getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(areaCircle, shapes[0]->getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(radiusCircle * 2, shapes[0]->getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(radiusCircle * 2, shapes[0]->getFrameRect().width, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_CompositeShape_getFrameRect)
{
  std::shared_ptr<ushakov::Shape> circle =
      std::make_shared<ushakov::Circle>(ushakov::point_t{1.0, 1.0}, 1.0);

  std::shared_ptr<ushakov::Shape> rectangle =
      std::make_shared<ushakov::Rectangle>(1.0, 1.0, ushakov::point_t{1.0, 1.0});

  const double frameHeight = 2.0;
  const double frameWidth = 2.0;

  const ushakov::point_t framePos = {1.0, 1.0};

  ushakov::CompositeShape shapes;

  shapes.addShape(rectangle);
  shapes.addShape(circle);

  ushakov::Rectangle frameRectangle(shapes.getFrameRect());

  BOOST_CHECK_CLOSE(frameRectangle.getHeight(), frameHeight, ACCURACY);
  BOOST_CHECK_CLOSE(frameRectangle.getWidth(), frameWidth, ACCURACY);
  BOOST_CHECK_CLOSE(framePos.x, frameRectangle.getPosition().x, ACCURACY);
  BOOST_CHECK_CLOSE(framePos.y, frameRectangle.getPosition().y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_correct_move_CompositeShape)
{
  const double X = 1.8;
  const double Y = 3.0;

  std::shared_ptr<ushakov::Shape> circle =
      std::make_shared<ushakov::Circle>(ushakov::point_t{X, Y}, 1.0);

  std::shared_ptr<ushakov::Shape> rectangle =
      std::make_shared<ushakov::Rectangle>(9.4, 2.4, ushakov::point_t{X, Y});

  const double DIFF_X = 1.0;
  const double DIFF_Y = 2.0;

  ushakov::CompositeShape shapes;

  shapes.addShape(rectangle);
  shapes.addShape(circle);

  shapes.move(DIFF_X, DIFF_Y);
  BOOST_CHECK_CLOSE(shapes[0]->getFrameRect().pos.x, X + DIFF_X, ACCURACY);
  BOOST_CHECK_CLOSE(shapes[0]->getFrameRect().pos.y, Y + DIFF_Y, ACCURACY);
  BOOST_CHECK_CLOSE(shapes[1]->getFrameRect().pos.x, X + DIFF_X, ACCURACY);
  BOOST_CHECK_CLOSE(shapes[1]->getFrameRect().pos.y, Y + DIFF_Y, ACCURACY);

  shapes.move({X, Y});
  BOOST_CHECK_CLOSE(shapes[0]->getFrameRect().pos.x, X, ACCURACY);
  BOOST_CHECK_CLOSE(shapes[0]->getFrameRect().pos.y, Y, ACCURACY);
  BOOST_CHECK_CLOSE(shapes[1]->getFrameRect().pos.x, X, ACCURACY);
  BOOST_CHECK_CLOSE(shapes[1]->getFrameRect().pos.y, Y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_copying_CompositeShape)
{
  std::shared_ptr<ushakov::Shape> shape =
      std::make_shared<ushakov::Circle>(ushakov::point_t{1.8, 4.2}, 8.1);

  ushakov::CompositeShape shapes1;

  shapes1.addShape(shape);

  ushakov::CompositeShape shapes2(shapes1);

  BOOST_CHECK_CLOSE(shapes1[0]->getPosition().x, shapes2[0]->getPosition().x, ACCURACY);
  BOOST_CHECK_CLOSE(shapes1[0]->getPosition().y, shapes2[0]->getPosition().y, ACCURACY);
  BOOST_CHECK_CLOSE(shapes1[0]->getArea(), shapes2[0]->getArea(), ACCURACY);

  ushakov::CompositeShape shapes3;
  shapes3 = shapes2;

  BOOST_CHECK_CLOSE(shapes3[0]->getPosition().x, shapes2[0]->getPosition().x, ACCURACY);
  BOOST_CHECK_CLOSE(shapes3[0]->getPosition().y, shapes2[0]->getPosition().y, ACCURACY);
  BOOST_CHECK_CLOSE(shapes3[0]->getArea(), shapes2[0]->getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_moving_CompositeShape)
{
  std::shared_ptr<ushakov::Shape> shape =
      std::make_shared<ushakov::Circle>(ushakov::point_t{1.8, 4.2}, 8.1);

  const double SHAPE_AREA = shape->getArea();
  const double SHAPE_CENTER_X = shape->getPosition().x;
  const double SHAPE_CENTER_Y = shape->getPosition().y;

  ushakov::CompositeShape shapes1;

  shapes1.addShape(shape);

  ushakov::CompositeShape shapes2(std::move(shapes1));

  BOOST_CHECK_CLOSE(SHAPE_CENTER_X, shapes2[0]->getPosition().x, ACCURACY);
  BOOST_CHECK_CLOSE(SHAPE_CENTER_Y, shapes2[0]->getPosition().y, ACCURACY);
  BOOST_CHECK_CLOSE(SHAPE_AREA, shapes2[0]->getArea(), ACCURACY);

  ushakov::CompositeShape shapes3;

  shapes3 = std::move(shapes2);

  BOOST_CHECK_CLOSE(SHAPE_CENTER_X, shapes3[0]->getPosition().x, ACCURACY);
  BOOST_CHECK_CLOSE(SHAPE_CENTER_Y, shapes3[0]->getPosition().y, ACCURACY);
  BOOST_CHECK_CLOSE(SHAPE_AREA, shapes3[0]->getArea(), ACCURACY);
}
