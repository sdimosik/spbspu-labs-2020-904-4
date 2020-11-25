#define BOOST_TEST_MODULE mytest

#include <memory>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "matrix.hpp"
#include "polygon.hpp"
#include "base-types.hpp"
#include "composite-shape.hpp"

const double PERMISSIBLE_ACCURACY = 0.0001;

BOOST_AUTO_TEST_CASE(test_rotate_circle)
{
  starikevich::Circle circle({ 1.0, 4.0 }, 1.0);
  const double height = circle.getFrameRect().height;
  const double width = circle.getFrameRect().width;
  circle.rotate(90);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, width, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, height, PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rotate_rectangle)
{
  starikevich::Rectangle rect({ 3.0, 1.0 }, 2.0, 2.0);
  const double height = rect.getFrameRect().height;
  const double width = rect.getFrameRect().width;
  rect.rotate(90);
  BOOST_CHECK_CLOSE(rect.getFrameRect().width, height, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(rect.getFrameRect().height, width, PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rotate_triangle)
{
  starikevich::Triangle triangle({ 4.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 3.0 });
  const double height = triangle.getFrameRect().height;
  const double width = triangle.getFrameRect().width;
  triangle.rotate(90);
  BOOST_CHECK_CLOSE(triangle.getFrameRect().width, height, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(triangle.getFrameRect().height, width, PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rotate_polygon)
{
  starikevich::point_t array1[] = { { 1.0, 0.0 }, { 0.0, 3.0 }, { 4.0, 6.0 }, { 5.0, 3.0 }, { 3.0, 0.0 } };
  starikevich::Polygon polygon(array1, 5);
  const double height = polygon.getFrameRect().height;
  const double width = polygon.getFrameRect().width;
  polygon.rotate(90);
  BOOST_CHECK_CLOSE(polygon.getFrameRect().width, height, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(polygon.getFrameRect().height, width, PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_point_polygon_constructor)
{
  starikevich::point_t array1[] = { { 1.0, 0.0 }, { 3.0, 2.0 }, { 4.0, 6.0 }, { 5.0, 3.0 }, { 3.0, 0.0 } };
  starikevich::point_t array2[] = { { 1.0, 0.0 }, { 2.5, 3.0 }, { 4.0, 6.0 }, { 5.0, 3.0 }, { 3.0, 0.0 } };
  starikevich::point_t array3[] = { { 0.0, 0.0 }, { 4.0, 5.0 }, { 0.0, 5.0 }, { 4.0, 0.0 } };
  BOOST_CHECK_THROW(starikevich::Polygon polygon(array1, 5), std::invalid_argument);
  BOOST_CHECK_THROW(starikevich::Polygon polygon(array2, 5), std::invalid_argument);
  BOOST_CHECK_THROW(starikevich::Polygon polygon(array3, 4), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_scaling_coefficient_polygon)
{
  starikevich::point_t array1[] = { { 1.0, 0.0 }, { 0.0, 3.0 }, { 4.0, 6.0 }, { 5.0, 3.0 }, { 3.0, 0.0 } };
  starikevich::Polygon polygon(array1, 5);
  BOOST_CHECK_THROW(polygon.scale(-6.5), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_permanency_size_polygon_moving)
{
  starikevich::point_t array1[] = { { 1.0, 0.0 }, { 0.0, 3.0 }, { 4.0, 6.0 }, { 5.0, 3.0 }, { 3.0, 0.0 } };
  starikevich::Polygon polygon(array1, 5);
  const double area = polygon.getArea();
  starikevich::rectangle_t frameRect = polygon.getFrameRect();

  polygon.move(17.6, 18.4);
  BOOST_CHECK_CLOSE(frameRect.width, polygon.getFrameRect().width, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.height, polygon.getFrameRect().height, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(area, polygon.getArea(), PERMISSIBLE_ACCURACY);

  polygon.move({ -17.6, 18.4 });
  BOOST_CHECK_CLOSE(frameRect.width, polygon.getFrameRect().width, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.height, polygon.getFrameRect().height, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(area, polygon.getArea(), PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_quadratic_change_area_polygon)
{
  starikevich::point_t array1[] = { { 1.0, 0.0 }, { 0.0, 3.0 }, { 4.0, 6.0 }, { 5.0, 3.0 }, { 3.0, 0.0 } };
  starikevich::Polygon polygon(array1, 5);
  const double area = polygon.getArea();
  const double coef = 6.5;
  polygon.scale(coef);
  BOOST_CHECK_CLOSE(area * coef * coef, polygon.getArea(), PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_too_small_index_polygon)
{
  starikevich::point_t array1[] = { { 1.0, 0.0 }, { 0.0, 3.0 } };
  BOOST_CHECK_THROW(starikevich::Polygon polygon(array1, 2), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_too_big_index_get_peak_coordinates_polygon)
{
  starikevich::point_t array1[] = { { 1.0, 0.0 }, { 0.0, 3.0 }, { 4.0, 6.0 }, { 5.0, 3.0 }, { 3.0, 0.0 } };
  starikevich::Polygon polygon(array1, 5);
  BOOST_CHECK_THROW(polygon.getPeakCoordinates(24), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_too_big_index_get_side_coordinates_polygon)
{
  starikevich::point_t array1[] = { { 1.0, 0.0 }, { 0.0, 3.0 }, { 4.0, 6.0 }, { 5.0, 3.0 }, { 3.0, 0.0 } };
  starikevich::Polygon polygon(array1, 5);
  BOOST_CHECK_THROW(polygon.getPeakCoordinates(24), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_get_area_polygon)
{
  starikevich::point_t array1[] = { { 1.0, 0.0 }, { 0.0, 3.0 }, { 4.0, 6.0 }, { 5.0, 3.0 }, { 3.0, 0.0 } };
  starikevich::Polygon polygon(array1, 5);
    const double area = 18.0;
    BOOST_CHECK_CLOSE(polygon.getArea(), area, PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_rotate_composite_shape)
{
  starikevich::CompositeShape array1;
  std::shared_ptr<starikevich::Shape> rect = std::make_shared<starikevich::Rectangle>(starikevich::Rectangle({ 7.0, 2.0 }, 2.0, 2.0));
  std::shared_ptr<starikevich::Shape> triangle = std::make_shared<starikevich::Triangle>(starikevich::Triangle({ 4.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 3.0 }));
  std::shared_ptr<starikevich::Shape> circle = std::make_shared<starikevich::Circle>(starikevich::Circle({ 1.0, 5.0 }, 1.0));
  array1.addShape(rect);
  array1.addShape(triangle);
  array1.addShape(circle);
  array1.rotate(90);
  starikevich::rectangle_t frameRect = array1.getFrameRect();
  BOOST_CHECK_CLOSE(frameRect.pos.x, 4, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.pos.y, 3, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.width, 6, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(frameRect.height, 8, PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_layering)
{
  std::shared_ptr<starikevich::Shape> rect = std::make_shared<starikevich::Rectangle>(starikevich::Rectangle({ 1.0, 2.0 }, 2.0, 2.0));
  std::shared_ptr<starikevich::Shape> triangle = std::make_shared<starikevich::Triangle>(starikevich::Triangle({ 4.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 3.0 }));
  std::shared_ptr<starikevich::Shape> circle = std::make_shared<starikevich::Circle>(starikevich::Circle({ 1.0, 5.0 }, 1.0));
  starikevich::CompositeShape compositeShape;
  compositeShape.addShape(rect);
  compositeShape.addShape(triangle);
  compositeShape.addShape(circle);
  starikevich::Matrix matrix = compositeShape.makeMatrix();
  BOOST_CHECK(matrix.getShapeCount(0) == 2);
  BOOST_CHECK(matrix.getShapeCount(1) == 1);
}
