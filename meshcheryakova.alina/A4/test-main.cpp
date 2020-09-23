#define BOOST_TEST_MODULE mytest

#include <memory>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "Matrix.hpp"

const double ACCURACY = 0.0001;

BOOST_AUTO_TEST_CASE(test_correct_separation_of_matrix)
{
  meshcheryakova::CompositeShape array(3);
  meshcheryakova::Rectangle rectangle1(8, 2.5, {7, 0});
  meshcheryakova::Rectangle rectangle2(4, 1.5, {10, 2});
  meshcheryakova::Circle circle1({12, 2}, 3);
  std::shared_ptr<meshcheryakova::Shape> shape1 = std::make_shared<meshcheryakova::Circle>(circle1);
  std::shared_ptr<meshcheryakova::Shape> shape2 = std::make_shared<meshcheryakova::Rectangle>(rectangle1);
  std::shared_ptr<meshcheryakova::Shape> shape3 = std::make_shared<meshcheryakova::Rectangle>(rectangle2);
  array.addElement(shape1);
  array.addElement(shape2);
  array.addElement(shape3);
  meshcheryakova::Matrix matrix;
  matrix.separate(array);

  BOOST_CHECK_EQUAL(matrix.getShape(0,0), shape1);
  BOOST_CHECK_EQUAL(matrix.getShape(1,0), shape2);
  BOOST_CHECK_EQUAL(matrix.getShape(2,0), shape3);
  BOOST_CHECK_EQUAL(matrix.getRows(), 3);
  BOOST_CHECK_EQUAL(matrix.getColumns(), 1);
}

BOOST_AUTO_TEST_CASE(test_get_shape_of_matrix)
{
  meshcheryakova::Matrix matrix;
  BOOST_CHECK_THROW(matrix.getShape(1,2), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_copy_constructor_of_matrix)
{
  meshcheryakova::CompositeShape array(3);
  meshcheryakova::Rectangle rectangle1(8, 2.5, {7, 0});
  meshcheryakova::Rectangle rectangle2(4, 1.5, {10, 2});
  meshcheryakova::Circle circle1({12, 2}, 3);
  std::shared_ptr<meshcheryakova::Shape> shape1 = std::make_shared<meshcheryakova::Circle>(circle1);
  std::shared_ptr<meshcheryakova::Shape> shape2 = std::make_shared<meshcheryakova::Rectangle>(rectangle1);
  std::shared_ptr<meshcheryakova::Shape> shape3 = std::make_shared<meshcheryakova::Rectangle>(rectangle2);
  array.addElement(shape1);
  array.addElement(shape2);
  array.addElement(shape3);
  meshcheryakova::Matrix matrix;
  matrix.separate(array);
  meshcheryakova::Matrix copy_of_matrix(matrix);
  BOOST_CHECK(copy_of_matrix.getShape(0,0) == matrix.getShape(0,0));
  BOOST_CHECK(copy_of_matrix.getShape(1,0) == matrix.getShape(1,0));
  BOOST_CHECK(copy_of_matrix.getShape(2,0) == matrix.getShape(2,0));
}

BOOST_AUTO_TEST_CASE(test_move_constructor_of_matrix)
{
  meshcheryakova::CompositeShape array(3);
  meshcheryakova::Rectangle rectangle1(8, 2.5, {7, 0});
  meshcheryakova::Rectangle rectangle2(4, 1.5, {10, 2});
  meshcheryakova::Circle circle1({12, 2}, 3);
  std::shared_ptr<meshcheryakova::Shape> shape1 = std::make_shared<meshcheryakova::Circle>(circle1);
  std::shared_ptr<meshcheryakova::Shape> shape2 = std::make_shared<meshcheryakova::Rectangle>(rectangle1);
  std::shared_ptr<meshcheryakova::Shape> shape3 = std::make_shared<meshcheryakova::Rectangle>(rectangle2);
  array.addElement(shape1);
  array.addElement(shape2);
  array.addElement(shape3);
  meshcheryakova::Matrix matrix;
  matrix.separate(array);
  meshcheryakova::Matrix move_of_matrix(std::move(matrix));
  BOOST_CHECK(move_of_matrix.getShape(0,0) == shape1);
  BOOST_CHECK(move_of_matrix.getShape(1,0) == shape2);
  BOOST_CHECK(move_of_matrix.getShape(2,0) == shape3);
}

BOOST_AUTO_TEST_CASE(test_rotate_of_circle)
{
  meshcheryakova::Circle circle1({12, 2}, 3);
  double area_cir = circle1.getArea();
  meshcheryakova::rectangle_t frame_cir = circle1.getFrameRect();
  circle1.rotate(90);
  BOOST_CHECK(circle1.getArea() == area_cir);
  BOOST_CHECK(circle1.getFrameRect().height == frame_cir.height);
  BOOST_CHECK(circle1.getFrameRect().width == frame_cir.width);
}

BOOST_AUTO_TEST_CASE(test_rotate_of_rectangle)
{
  meshcheryakova::Circle rectangle1({12, 2}, 3);
  double area_rec = rectangle1.getArea();
  meshcheryakova::rectangle_t frame_rec = rectangle1.getFrameRect();
  rectangle1.rotate(90);
  BOOST_CHECK(rectangle1.getArea() == area_rec);
  BOOST_CHECK(rectangle1.getFrameRect().height == frame_rec.width);
  BOOST_CHECK(rectangle1.getFrameRect().width == frame_rec.height);
}

BOOST_AUTO_TEST_CASE(test_rotate_of_composite_shape)
{
  meshcheryakova::CompositeShape array(2);
  meshcheryakova::Rectangle rectangle1(2, 4, {0, 0});
  meshcheryakova::rectangle_t frame_rec = rectangle1.getFrameRect();
  double area_rec = rectangle1.getArea();
  meshcheryakova::Circle circle1({4, 0}, 1);
  meshcheryakova::rectangle_t frame_cir = circle1.getFrameRect();
  double area_cir = circle1.getArea();
  std::shared_ptr<meshcheryakova::Shape> shape1 = std::make_shared<meshcheryakova::Circle>(circle1);
  std::shared_ptr<meshcheryakova::Shape> shape2 = std::make_shared<meshcheryakova::Rectangle>(rectangle1);
  array.addElement(shape1);
  array.addElement(shape2);
  array.rotate(90);
  BOOST_CHECK(array.getArea() == area_rec + area_cir);
  BOOST_CHECK_CLOSE(array.getFrameRect().width, 7, ACCURACY);
  BOOST_CHECK_CLOSE(array.getFrameRect().height, 6, ACCURACY);
  BOOST_CHECK_CLOSE(array[1]->getFrameRect().height, frame_rec.width, ACCURACY);
  BOOST_CHECK_CLOSE(array[1]->getFrameRect().width, frame_rec.height, ACCURACY);
  BOOST_CHECK(array[0]->getFrameRect().height == frame_cir.height);
  BOOST_CHECK(array[0]->getFrameRect().width == frame_cir.width);
}

BOOST_AUTO_TEST_CASE(test_operator_copy_matrix)
{
  meshcheryakova::CompositeShape array(3);
  meshcheryakova::Rectangle rectangle1(8, 2.5, {7, 0});
  meshcheryakova::Rectangle rectangle2(4, 1.5, {10, 2});
  meshcheryakova::Circle circle1({12, 2}, 3);
  std::shared_ptr<meshcheryakova::Shape> shape1 = std::make_shared<meshcheryakova::Circle>(circle1);
  std::shared_ptr<meshcheryakova::Shape> shape2 = std::make_shared<meshcheryakova::Rectangle>(rectangle1);
  std::shared_ptr<meshcheryakova::Shape> shape3 = std::make_shared<meshcheryakova::Rectangle>(rectangle2);
  array.addElement(shape1);
  array.addElement(shape2);
  array.addElement(shape3);
  meshcheryakova::Matrix matrix;
  matrix.separate(array);
  meshcheryakova::Matrix copy_of_matrix;
  copy_of_matrix = matrix;
  BOOST_CHECK(copy_of_matrix.getShape(0,0) == matrix.getShape(0,0));
  BOOST_CHECK(copy_of_matrix.getShape(1,0) == matrix.getShape(1,0));
  BOOST_CHECK(copy_of_matrix.getShape(2,0) == matrix.getShape(2,0));
}


