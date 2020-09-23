#define BOOST_TEST_MODULE testA4

#include <stdexcept>
#include <memory>

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

const double angle = 45.0;
const double accuracy = 0.000001;

BOOST_AUTO_TEST_CASE(check_matrix_copy_constructor)
{
  spasoevich::Rectangle rect({ { 10.0, 3.0 }, 4.0, 2.0 });
  spasoevich::Circle circ({ 4.0, 4.0 }, 2.0);

  spasoevich::Matrix matrix;
  matrix.addShape(std::make_shared<spasoevich::Rectangle>(rect));
  matrix.addShape(std::make_shared<spasoevich::Circle>(circ));

  spasoevich::Matrix testMatrix(matrix);

  BOOST_CHECK_EQUAL(matrix.getRows(), testMatrix.getRows());
  BOOST_CHECK_EQUAL(matrix.getColumns(), testMatrix.getColumns());
}

BOOST_AUTO_TEST_CASE(check_rotating_circle)
{
  spasoevich::Circle circle({ 0.0, 0.0 }, 6.7);
  const double area = circle.getArea();
  circle.rotate(angle);
  BOOST_CHECK_CLOSE(area, circle.getArea(), accuracy);
}

BOOST_AUTO_TEST_CASE(check_rotating_rectangle)
{
  spasoevich::Rectangle rectangle({ 0.0, 0.0 }, 5.6, 3.6);
  const double area = rectangle.getArea();
  rectangle.rotate(angle);
  BOOST_CHECK_CLOSE(area, rectangle.getArea(), accuracy);
}

BOOST_AUTO_TEST_CASE(check_rotating_composite_shape)
{
  spasoevich::Rectangle rectangle({ 0.0, 0.0 }, 2.0, 3.0);
  spasoevich::Circle circle({ 0.0, 2.0 }, 1.0);
  spasoevich::CompositeShape::shape_ptr shape1 = std::make_shared<spasoevich::Rectangle>(rectangle);
  spasoevich::CompositeShape::shape_ptr shape2 = std::make_shared<spasoevich::Circle>(circle);
  spasoevich::CompositeShape compositeShape;
  compositeShape.addShape(shape1);
  compositeShape.addShape(shape2);
  double totalArea = compositeShape.getArea();
  compositeShape.rotate(2 * angle);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), totalArea, accuracy);
}
