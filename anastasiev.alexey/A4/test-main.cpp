#define BOOST_TEST_MODULE myTest

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"
#include "polygon.hpp"
#include "matrix.hpp"
const double ACCURACY = 0.001;

BOOST_AUTO_TEST_CASE(test_circle_rotate)
{
  anastasiev::Circle circle(5, {0, 0});
  const double area = circle.getArea();
  anastasiev::point_t pos = circle.getPosition();
  circle.rotate(30);
  BOOST_CHECK_CLOSE(area, circle.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(pos.x, circle.getPosition().x, ACCURACY);
  BOOST_CHECK_CLOSE(pos.y, circle.getPosition().y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rectangle_rotate)
{
  anastasiev::Rectangle rectangle(5, 3, {0, 0});
  const double area = rectangle.getArea();
  anastasiev::point_t pos = rectangle.getPosition();
  const double width = rectangle.getFrameRect().width;
  const double height = rectangle.getFrameRect().height;
  rectangle.rotate(90);
  BOOST_CHECK_CLOSE(area, rectangle.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(pos.x, rectangle.getPosition().x, ACCURACY);
  BOOST_CHECK_CLOSE(pos.y, rectangle.getPosition().y, ACCURACY);
  BOOST_CHECK_CLOSE(width, rectangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(height, rectangle.getFrameRect().width, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_triangle_rotate)
{
  anastasiev::Triangle triangle({0, 0}, {0, 3}, {4, 0});
  const double area = triangle.getArea();
  anastasiev::point_t pos = triangle.getPosition();
  const double width = triangle.getFrameRect().width;
  const double height = triangle.getFrameRect().height;
  triangle.rotate(90);
  BOOST_CHECK_CLOSE(area, triangle.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(pos.x, triangle.getPosition().x, ACCURACY);
  BOOST_CHECK_CLOSE(pos.y, triangle.getPosition().y, ACCURACY);
  BOOST_CHECK_CLOSE(width, triangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(height, triangle.getFrameRect().width, ACCURACY);

}

BOOST_AUTO_TEST_CASE(test_composite_shape_rotate)
{
  anastasiev::CompositeShape compShape; 
  std::shared_ptr<anastasiev::Shape> rectangle1
      = std::make_shared<anastasiev::Rectangle>(anastasiev::Rectangle(3, 3, {3.5, 2.5}));
  std::shared_ptr<anastasiev::Shape> rectangle2
      = std::make_shared<anastasiev::Rectangle>(anastasiev::Rectangle(3, 3, {6.5, 2.5}));
  compShape.add(rectangle1);
  compShape.add(rectangle2);
  const double area = compShape.getArea();
  anastasiev::point_t pos = compShape.getFrameRect().pos;
  const double width = compShape.getFrameRect().width;
  const double height = compShape.getFrameRect().height;
  compShape.rotate(90);
  BOOST_CHECK_CLOSE(area, compShape.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(pos.x, compShape.getFrameRect().pos.x, ACCURACY);
  BOOST_CHECK_CLOSE(pos.y, compShape.getFrameRect().pos.y, ACCURACY);
  BOOST_CHECK_CLOSE(width, compShape.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(height, compShape.getFrameRect().width, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_polygon_invalid_argument)
{
  BOOST_CHECK_THROW(anastasiev::Polygon polygon({{0, 0}, {10, 1}}), std::invalid_argument);
  BOOST_CHECK_THROW(anastasiev::Polygon polygon({{0, 0}, {0, 0}, {0, 1}}), std::invalid_argument);
  BOOST_CHECK_THROW(anastasiev::Polygon polygon({{0, 0}, {0, 3}, {1, 1}, {3, 0}}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_polygon_invalid_argument_scale)
{
  anastasiev::Polygon polygon({{0, 0}, {0, 3}, {3, 0}});
  BOOST_CHECK_THROW(polygon.scale(-3), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_polygon_scale)
{
  anastasiev::Polygon polygon({{0, 0}, {0, 3}, {3, 0}});
  const double area = polygon.getArea(), factor = 2;
  polygon.scale(factor);
  BOOST_CHECK_CLOSE(area * factor * factor, polygon.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_polygon_rotate)
{
  anastasiev::Polygon polygon({{0, 0}, {0, 3}, {4, 0}});
  const double area = polygon.getArea();
  anastasiev::point_t pos = polygon.getPosition();
  const double width = polygon.getFrameRect().width;
  const double height = polygon.getFrameRect().height;
  polygon.rotate(90);
  BOOST_CHECK_CLOSE(area, polygon.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(pos.x, polygon.getPosition().x, ACCURACY);
  BOOST_CHECK_CLOSE(pos.y, polygon.getPosition().y, ACCURACY);
  BOOST_CHECK_CLOSE(width, polygon.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(height, polygon.getFrameRect().width, ACCURACY);

}

BOOST_AUTO_TEST_CASE(test_matrix_null_shape)
{
  anastasiev::Matrix matrix;
  BOOST_CHECK_THROW(matrix.addShape(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_matrix_out_of_range)
{
  anastasiev::Matrix matrix;
  BOOST_CHECK_THROW(matrix.getShape(0,0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_matrix_correct_layering)
{
  std::shared_ptr<anastasiev::Shape> rectangle
      = std::make_shared<anastasiev::Rectangle>(anastasiev::Rectangle(2, 2, {0, 0}));
  std::shared_ptr<anastasiev::Shape>  polygon
      = std::make_shared<anastasiev::Polygon>(anastasiev::Polygon({{50, 50}, {50, 53}, {53, 50}}));
  std::shared_ptr<anastasiev::Shape>  triangle
      = std::make_shared<anastasiev::Triangle>(anastasiev::Triangle({0, 0}, {0, 3}, {3, 0}));
  anastasiev::Matrix matrix;
  matrix.addShape(rectangle);
  matrix.addShape(polygon);
  matrix.addShape(triangle);
  BOOST_CHECK_EQUAL(matrix.getShape(0,0), rectangle);
  BOOST_CHECK_EQUAL(matrix.getShape(0,1), polygon);
  BOOST_CHECK_EQUAL(matrix.getShape(1,0), triangle);
}

BOOST_AUTO_TEST_CASE(test_composite_shape_getLayered)
{
  std::shared_ptr<anastasiev::Shape> rectangle
      = std::make_shared<anastasiev::Rectangle>(anastasiev::Rectangle(2, 2, {0, 0}));
  std::shared_ptr<anastasiev::Shape>  polygon
      = std::make_shared<anastasiev::Polygon>(anastasiev::Polygon({{50, 50}, {50, 53}, {53, 50}}));
  std::shared_ptr<anastasiev::Shape>  triangle
      = std::make_shared<anastasiev::Triangle>(anastasiev::Triangle({0, 0}, {0, 3}, {3, 0}));
  anastasiev::CompositeShape compShape;
  compShape.add(rectangle);
  compShape.add(polygon);
  compShape.add(triangle);
  anastasiev::Matrix matrix = compShape.getLayered();
  BOOST_CHECK_EQUAL(matrix.getShape(0,0), rectangle);
  BOOST_CHECK_EQUAL(matrix.getShape(0,1), polygon);
  BOOST_CHECK_EQUAL(matrix.getShape(1,0), triangle);
}
