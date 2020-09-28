#define BOOST_TEST_MODULE A1_TEST

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include "polygon.hpp"

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

  const double circleArea = circle.getArea();
  const double coefficient = 2.0;

  circle.scale(coefficient);

  BOOST_CHECK_CLOSE(circleArea * coefficient * coefficient, circle.getArea(), ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_scale_area_rectangle)
{
  ushakov::Rectangle rectangle(1.0, 3.0, {0.0, 0.0});

  const double rectangleArea = rectangle.getArea();
  const double coefficient = 2.0;

  rectangle.scale(coefficient);

  BOOST_CHECK_CLOSE(rectangleArea * coefficient * coefficient, rectangle.getArea(), ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_scale_area_triangle)
{
  ushakov::Triangle triangle({0.0, 0.0}, {0.0, 3.0}, {4.0, 0.0});

  const double triangleArea = triangle.getArea();
  const double coefficient = 2.0;

  triangle.scale(coefficient);

  BOOST_CHECK_CLOSE(triangleArea * coefficient * coefficient, triangle.getArea(), ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_move_constancy_circle)
{
  ushakov::Circle circle({0.0, 0.0}, 1.0);
  ushakov::rectangle_t circleFrame = circle.getFrameRect();

  const double circleArea = circle.getArea();

  circle.move(2.0, -3.0);

  BOOST_CHECK_CLOSE(circleFrame.width, circle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(circleFrame.height, circle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(circleArea, circle.getArea(), ACCURACY);

  circle.move({1.0, 1.0});

  BOOST_CHECK_CLOSE(circleFrame.width, circle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(circleFrame.height, circle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(circleArea, circle.getArea(), ACCURACY);
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

  const double triangleArea = triangle.getArea();

  triangle.move(2.0, -3.0);

  BOOST_CHECK_CLOSE(triangleFrame.width, triangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(triangleFrame.height, triangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(triangleArea, triangle.getArea(), ACCURACY);

  triangle.move({1.0, 1.0});

  BOOST_CHECK_CLOSE(triangleFrame.width, triangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(triangleFrame.height, triangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(triangleArea, triangle.getArea(), ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_correct_move_circle)
{
  ushakov::Circle circle({0.0, 0.0}, 1.0);

  const double diffX = 3.0;
  const double diffY = 4.0;
  const double X = circle.getPosition().x;
  const double Y = circle.getPosition().y;

  circle.move(diffX, diffY);

  BOOST_CHECK_CLOSE(circle.getPosition().x, diffX + X, ACCURACY);
  BOOST_CHECK_CLOSE(circle.getPosition().y, diffY + Y, ACCURACY);

  circle.move({diffX, diffY});

  BOOST_CHECK_CLOSE(circle.getPosition().x, diffX, ACCURACY);
  BOOST_CHECK_CLOSE(circle.getPosition().y, diffY, ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_correct_move_rectangle)
{
  ushakov::Rectangle rectangle(1.0, 3.0, {0.0, 0.0});

  const double diffX = 3.0;
  const double diffY = 4.0;
  const double X = rectangle.getPosition().x;
  const double Y = rectangle.getPosition().y;

  rectangle.move(diffX, diffY);

  BOOST_CHECK_CLOSE(rectangle.getPosition().x, diffX + X, ACCURACY);
  BOOST_CHECK_CLOSE(rectangle.getPosition().y, diffY + Y, ACCURACY);

  rectangle.move({diffX, diffY});

  BOOST_CHECK_CLOSE(rectangle.getPosition().x, diffX, ACCURACY);
  BOOST_CHECK_CLOSE(rectangle.getPosition().y, diffY, ACCURACY);
};

BOOST_AUTO_TEST_CASE(test_correct_move_triangle)
{
  ushakov::Triangle triangle({0.0, 0.0}, {0.0, 3.0}, {4.0, 0.0});

  const double diffX = 3.0;
  const double diffY = 4.0;
  const double X = triangle.getPosition().x;
  const double Y = triangle.getPosition().y;

  triangle.move(diffX, diffY);

  BOOST_CHECK_CLOSE(triangle.getPosition().x, diffX + X, ACCURACY);
  BOOST_CHECK_CLOSE(triangle.getPosition().y, diffY + Y, ACCURACY);

  triangle.move({diffX, diffY});

  BOOST_CHECK_CLOSE(triangle.getPosition().x, diffX, ACCURACY);
  BOOST_CHECK_CLOSE(triangle.getPosition().y, diffY, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_CompositeShape_addShape)
{
  ushakov::CompositeShape shapes;
  std::shared_ptr<ushakov::Shape> shape = nullptr;

  BOOST_CHECK_THROW(shapes.addShape(shape), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_empty_shape_CompositeShape_addShape)
{
  std::shared_ptr<ushakov::CompositeShape> shape;
  shape = std::make_shared<ushakov::CompositeShape>();
  ushakov::CompositeShape compositeShape;

  BOOST_CHECK_THROW(compositeShape.addShape(shape), std::invalid_argument);
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

  std::shared_ptr<ushakov::Shape> circle;
  circle = std::make_shared<ushakov::Circle>(ushakov::point_t{1.8, 4.2}, 8.1);

  shapes.addShape(circle);

  BOOST_CHECK_THROW(shapes[1], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_parameter_CompositeShape_scale)
{
  ushakov::CompositeShape shapes;

  std::shared_ptr<ushakov::Shape> circle;
  circle = std::make_shared<ushakov::Circle>(ushakov::point_t{1.8, 4.2}, 8.1);

  shapes.addShape(circle);

  BOOST_CHECK_THROW(shapes.scale(-1.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_scale_CompositeShape)
{
  std::shared_ptr<ushakov::Shape> rectangle;
  rectangle = std::make_shared<ushakov::Rectangle>(11.0, 10.0, ushakov::point_t{1.0, 1.0});

  std::shared_ptr<ushakov::Shape> circle = std::make_shared<ushakov::Circle>(ushakov::Circle({10.0, 10.0}, 10.0));

  ushakov::CompositeShape array;

  array.addShape(circle);
  array.addShape(rectangle);

  const double areaRect = rectangle->getArea();
  const double coefficient = 2.0;
  const double areaCircle = circle->getArea();

  array.scale(coefficient);

  BOOST_CHECK_CLOSE(areaCircle * coefficient * coefficient, circle->getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(areaRect * coefficient * coefficient, rectangle->getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_CompositeShape_getSize)
{
  ushakov::CompositeShape shapes;

  std::shared_ptr<ushakov::Shape> circle;
  circle = std::make_shared<ushakov::Circle>(ushakov::point_t{1.8, 4.2}, 8.1);

  std::shared_ptr<ushakov::Shape> rectangle;
  rectangle = std::make_shared<ushakov::Rectangle>(9.4, 2.4, ushakov::point_t{3.0, 7.1});

  shapes.addShape(rectangle);

  shapes.addShape(circle);

  BOOST_CHECK(shapes.getSize() == 2);
}

BOOST_AUTO_TEST_CASE(test_CompositeShape_getArea)
{
  ushakov::CompositeShape shapes;

  std::shared_ptr<ushakov::Shape> circle;
  circle = std::make_shared<ushakov::Circle>(ushakov::point_t{1.8, 4.2}, 8.1);

  std::shared_ptr<ushakov::Shape> rectangle;
  rectangle = std::make_shared<ushakov::Rectangle>(9.4, 2.4, ushakov::point_t{3.0, 7.1});

  const double area = circle->getArea() + rectangle->getArea();

  shapes.addShape(rectangle);
  shapes.addShape(circle);

  BOOST_CHECK(shapes.getArea() == area);
}

BOOST_AUTO_TEST_CASE(test_constancy_parameters_AfterMove_CompositeShape)
{
  ushakov::Circle circle(ushakov::point_t{1.8, 4.2}, 8.1);

  std::shared_ptr<ushakov::Shape> shape1;
  shape1 = std::make_shared<ushakov::Circle>(circle);

  const double circleArea = circle.getArea();
  const double circleRadius = circle.getRadius();

  ushakov::Rectangle rectangle(9.4, 2.4, ushakov::point_t{3.0, 7.1});

  std::shared_ptr<ushakov::Shape> shape2;
  shape2 = std::make_shared<ushakov::Rectangle>(rectangle);

  const double rectangleArea = rectangle.getArea();
  const double rectangleHeight = rectangle.getHeight();
  const double rectangleWidth = rectangle.getWidth();

  ushakov::CompositeShape shapes;

  shapes.addShape(shape1);
  shapes.addShape(shape2);

  shapes.move(ushakov::point_t{3.9, 7.2});

  BOOST_CHECK_CLOSE(rectangleArea, shapes[1]->getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(rectangleHeight, shapes[1]->getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(rectangleWidth, shapes[1]->getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(circleArea, shapes[0]->getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(circleRadius * 2, shapes[0]->getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(circleRadius * 2, shapes[0]->getFrameRect().width, ACCURACY);

  shapes.move(1.0, 2.0);

  BOOST_CHECK_CLOSE(rectangleArea, shapes[1]->getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(rectangleHeight, shapes[1]->getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(rectangleWidth, shapes[1]->getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(circleArea, shapes[0]->getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(circleRadius * 2, shapes[0]->getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(circleRadius * 2, shapes[0]->getFrameRect().width, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_CompositeShape_getFrameRect)
{
  std::shared_ptr<ushakov::Shape> circle;
  circle = std::make_shared<ushakov::Circle>(ushakov::point_t{1.0, 1.0}, 1.0);

  std::shared_ptr<ushakov::Shape> rectangle;
  rectangle = std::make_shared<ushakov::Rectangle>(1.0, 1.0, ushakov::point_t{1.0, 1.0});

  const double frameHeight = 2.0;
  const double frameWidth = 2.0;

  const ushakov::point_t framePosition = {1.0, 1.0};

  ushakov::CompositeShape shapes;

  shapes.addShape(rectangle);
  shapes.addShape(circle);

  ushakov::Rectangle frameRectangle(shapes.getFrameRect().width, shapes.getFrameRect().height, shapes.getFrameRect().pos);

  BOOST_CHECK_CLOSE(frameRectangle.getHeight(), frameHeight, ACCURACY);
  BOOST_CHECK_CLOSE(frameRectangle.getWidth(), frameWidth, ACCURACY);
  BOOST_CHECK_CLOSE(framePosition.x, frameRectangle.getPosition().x, ACCURACY);
  BOOST_CHECK_CLOSE(framePosition.y, frameRectangle.getPosition().y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_correct_move_CompositeShape)
{
  const double tempX = 1.8;
  const double tempY = 3.0;

  std::shared_ptr<ushakov::Shape> circle;
  circle = std::make_shared<ushakov::Circle>(ushakov::point_t{tempX, tempY}, 1.0);

  std::shared_ptr<ushakov::Shape> rectangle;
  rectangle = std::make_shared<ushakov::Rectangle>(9.4, 2.4, ushakov::point_t{tempX, tempY});

  const double diffX = 1.0;
  const double diffY = 2.0;

  ushakov::CompositeShape shapes;

  shapes.addShape(rectangle);
  shapes.addShape(circle);

  shapes.move(diffX, diffY);
  BOOST_CHECK_CLOSE(shapes[0]->getFrameRect().pos.x, tempX + diffX, ACCURACY);
  BOOST_CHECK_CLOSE(shapes[0]->getFrameRect().pos.y, tempY + diffY, ACCURACY);
  BOOST_CHECK_CLOSE(shapes[1]->getFrameRect().pos.x, tempX + diffX, ACCURACY);
  BOOST_CHECK_CLOSE(shapes[1]->getFrameRect().pos.y, tempY + diffY, ACCURACY);

  shapes.move({tempX, tempY});
  BOOST_CHECK_CLOSE(shapes[0]->getFrameRect().pos.x, tempX, ACCURACY);
  BOOST_CHECK_CLOSE(shapes[0]->getFrameRect().pos.y, tempY, ACCURACY);
  BOOST_CHECK_CLOSE(shapes[1]->getFrameRect().pos.x, tempX, ACCURACY);
  BOOST_CHECK_CLOSE(shapes[1]->getFrameRect().pos.y, tempY, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_copying_CompositeShape)
{
  std::shared_ptr<ushakov::Shape> shape;
  shape = std::make_shared<ushakov::Circle>(ushakov::point_t{1.8, 4.2}, 8.1);

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
  std::shared_ptr<ushakov::Shape> shape;
  shape = std::make_shared<ushakov::Circle>(ushakov::point_t{1.8, 4.2}, 8.1);

  const double shapeArea = shape->getArea();
  const double shapeCenterX = shape->getPosition().x;
  const double shapeCenterY = shape->getPosition().y;

  ushakov::CompositeShape shapes1;

  shapes1.addShape(shape);

  ushakov::CompositeShape shapes2(std::move(shapes1));

  BOOST_CHECK_CLOSE(shapeCenterX, shapes2[0]->getPosition().x, ACCURACY);
  BOOST_CHECK_CLOSE(shapeCenterY, shapes2[0]->getPosition().y, ACCURACY);
  BOOST_CHECK_CLOSE(shapeArea, shapes2[0]->getArea(), ACCURACY);

  ushakov::CompositeShape shapes3;

  shapes3 = std::move(shapes2);

  BOOST_CHECK_CLOSE(shapeCenterX, shapes3[0]->getPosition().x, ACCURACY);
  BOOST_CHECK_CLOSE(shapeCenterY, shapes3[0]->getPosition().y, ACCURACY);
  BOOST_CHECK_CLOSE(shapeArea, shapes3[0]->getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rotate_circle)
{
  ushakov::Circle circle({0.0, 0.0}, 5.0);

  const double frameHeight = circle.getFrameRect().height;
  const double frameWidth = circle.getFrameRect().width;

  circle.rotate(90);

  BOOST_CHECK_CLOSE(circle.getFrameRect().width, frameWidth, ACCURACY);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, frameHeight, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rotate_rectangle)
{
  ushakov::Rectangle rectangle(5.0, 10.0, {0.0, 0.0});

  const double frameHeight = rectangle.getFrameRect().height;
  const double frameWidth = rectangle.getFrameRect().width;

  rectangle.rotate(90);

  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, frameHeight, ACCURACY);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, frameWidth, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rotate_triangle)
{
  ushakov::Triangle triangle({3.0, 0.0}, {-2.0, 3.0}, {-2.0, -3.0});

  const double newFrameHeight = triangle.getFrameRect().width;
  const double newFrameWidth = triangle.getFrameRect().height;

  triangle.rotate(90);

  BOOST_CHECK_CLOSE(triangle.getFrameRect().width, newFrameWidth, ACCURACY);
  BOOST_CHECK_CLOSE(triangle.getFrameRect().height, newFrameHeight, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rotate_CompositeShape)
{
  ushakov::CompositeShape array;
  std::shared_ptr<ushakov::Shape> rectangle1;
  rectangle1 = std::make_shared<ushakov::Rectangle>(ushakov::Rectangle(4.0, 4.0, {-3.0, -5.0}));
  std::shared_ptr<ushakov::Shape> rectangle2;
  rectangle2 = std::make_shared<ushakov::Rectangle>(ushakov::Rectangle(4.0, 4.0, {4.0, 2.0}));

  array.addShape(rectangle1);
  array.addShape(rectangle2);

  ushakov::rectangle_t frameRectangle = array.getFrameRect();

  BOOST_CHECK_CLOSE(frameRectangle.pos.x, 0.5, ACCURACY);
  BOOST_CHECK_CLOSE(frameRectangle.pos.y, -1.5, ACCURACY);
  BOOST_CHECK_CLOSE(frameRectangle.width, 11, ACCURACY);
  BOOST_CHECK_CLOSE(frameRectangle.height, 11, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_index_is_out_of_range_layer)
{
  ushakov::Matrix matrix;

  BOOST_CHECK_THROW(matrix[0], std::out_of_range);

  ushakov::Circle circle({0.0, 0.0}, 5.0);
  std::shared_ptr<ushakov::Shape> shape = std::make_shared<ushakov::Circle>(circle);

  matrix.addShape(shape);

  BOOST_CHECK_THROW(matrix[0][1], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_pointer_addShape_matrix)
{
  ushakov::Matrix matrix;
  std::shared_ptr<ushakov::Shape> shape = nullptr;

  BOOST_CHECK_THROW(matrix.addShape(shape), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_copying_matrix)
{
  ushakov::Rectangle rectangle(3.0, 4.8, {2.4, 3.0});
  ushakov::Circle circle({0.0, 0.0}, 5.0);

  std::shared_ptr<ushakov::Shape> shape1 = std::make_shared<ushakov::Rectangle>(rectangle);
  std::shared_ptr<ushakov::Shape> shape2 = std::make_shared<ushakov::Circle>(circle);

  ushakov::Matrix matrix1;

  matrix1.addShape(shape1);
  matrix1.addShape(shape2);

  ushakov::Matrix matrix2(matrix1);

  BOOST_CHECK(matrix2[0][0] == shape1);
  BOOST_CHECK(matrix2[1][0] == shape2);

  ushakov::Matrix matrix3;

  matrix3 = matrix1;

  BOOST_CHECK(matrix3[0][0] == shape1);
  BOOST_CHECK(matrix3[1][0] == shape2);
}

BOOST_AUTO_TEST_CASE(test_moving_matrix)
{
  ushakov::Rectangle rectangle(3.0, 4.8, {2.4, 3.0});
  ushakov::Circle circle({0.0, 0.0}, 5.0);

  std::shared_ptr<ushakov::Shape> shape1 = std::make_shared<ushakov::Rectangle>(rectangle);
  std::shared_ptr<ushakov::Shape> shape2 = std::make_shared<ushakov::Circle>(circle);

  ushakov::Matrix matrix1;

  matrix1.addShape(shape1);
  matrix1.addShape(shape2);

  ushakov::Matrix matrix2(std::move(matrix1));

  BOOST_CHECK(matrix2[0][0] == shape1);
  BOOST_CHECK(matrix2[1][0] == shape2);

  ushakov::Matrix matrix3;

  matrix3 = std::move(matrix2);

  BOOST_CHECK(matrix3[0][0] == shape1);
  BOOST_CHECK(matrix3[1][0] == shape2);
}

BOOST_AUTO_TEST_CASE(test_addShape_matrix)
{
  ushakov::Rectangle rectangle(3.0, 4.8, {2.4, 3.0});
  ushakov::Circle circle({0.0, 0.0}, 5.0);

  std::shared_ptr<ushakov::Shape> shape1 = std::make_shared<ushakov::Rectangle>(rectangle);
  std::shared_ptr<ushakov::Shape> shape2 = std::make_shared<ushakov::Circle>(circle);

  ushakov::Matrix matrix;

  matrix.addShape(shape1);
  matrix.addShape(shape2);

  BOOST_CHECK(matrix[0][0] == shape1);
  BOOST_CHECK(matrix[1][0] == shape2);
  BOOST_CHECK(matrix.getRows() == 2);
  BOOST_CHECK(matrix.getColumns() == 1);
}

BOOST_AUTO_TEST_CASE(test_divide_CompositeShape)
{
  ushakov::Rectangle rectangle1(2.0, 4.0, {0.0, 0.0});
  ushakov::Circle circle1({0.5, 0.0}, 3.5);
  ushakov::Rectangle rectangle2(2.1, 2.8, {7.0, 5.0});
  ushakov::Circle circle2({7.1, 4.6}, 2.0);

  std::shared_ptr<ushakov::Shape> shape1 = std::make_shared<ushakov::Rectangle>(rectangle1);
  std::shared_ptr<ushakov::Shape> shape2 = std::make_shared<ushakov::Circle>(circle1);
  std::shared_ptr<ushakov::Shape> shape3 = std::make_shared<ushakov::Rectangle>(rectangle2);
  std::shared_ptr<ushakov::Shape> shape4 = std::make_shared<ushakov::Circle>(circle2);

  ushakov::CompositeShape compositeShape;
  compositeShape.addShape(shape1);
  compositeShape.addShape(shape2);
  compositeShape.addShape(shape3);
  compositeShape.addShape(shape4);

  ushakov::Matrix matrix = compositeShape.divide();
  BOOST_CHECK(matrix.getRows() == 2);
  BOOST_CHECK(matrix.getColumns() == 2);
  BOOST_CHECK(matrix[0][0] == shape1);
  BOOST_CHECK(matrix[1][0] == shape2);
}

BOOST_AUTO_TEST_CASE(test_index_is_out_of_range_matrix)
{
  ushakov::Matrix matrix;

  BOOST_CHECK_THROW(matrix[0], std::out_of_range);

  ushakov::Circle circle({0.0, 0.0}, 5.0);
  std::shared_ptr<ushakov::Shape> shape = std::make_shared<ushakov::Circle>(circle);

  matrix.addShape(shape);

  BOOST_CHECK_THROW(matrix[10][0], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_polygon_invalid_argument)
{
  BOOST_CHECK_THROW(ushakov::Polygon polygon({{0,  0}, {10, 1}}), std::invalid_argument);
  BOOST_CHECK_THROW(ushakov::Polygon polygon({{0, 0}, {0, 0}, {0, 1}}), std::invalid_argument);
  BOOST_CHECK_THROW(ushakov::Polygon polygon({{0, 0}, {0, 3}, {1, 1}, {3, 0}}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_polygon_invalid_argument_scale)
{
  ushakov::Polygon polygon({{0, 0}, {0, 3}, {3, 0}});

  BOOST_CHECK_THROW(polygon.scale(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_polygon_scale)
{
  ushakov::Polygon polygon({{0, 0}, {0, 3}, {3, 0}});

  const double area = polygon.getArea();
  const double coefficient = 2;

  polygon.scale(coefficient);

  BOOST_CHECK_CLOSE(area * coefficient * coefficient, polygon.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_polygon_rotate)
{
  ushakov::Polygon polygon({{0, 0}, {0, 3}, {4, 0}});

  const ushakov::point_t position = polygon.getPosition();
  const double frameHeight = polygon.getFrameRect().height;
  const double frameWidth = polygon.getFrameRect().width;
  const double area = polygon.getArea();

  polygon.rotate(90);

  BOOST_CHECK_CLOSE(area, polygon.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(position.x, polygon.getPosition().x, ACCURACY);
  BOOST_CHECK_CLOSE(position.y, polygon.getPosition().y, ACCURACY);
  BOOST_CHECK_CLOSE(frameWidth, polygon.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(frameHeight, polygon.getFrameRect().width, ACCURACY);

}
