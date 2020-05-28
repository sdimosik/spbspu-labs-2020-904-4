#define BOOST_TEST_MODULE mytest

#include <memory>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double ACCURACY = 0.0001;

BOOST_AUTO_TEST_CASE(test_invalid_get_index_compositeShape)
{
  meshcheryakova::CompositeShape array;
  BOOST_CHECK_THROW(array[-3], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_index_of_add_compositeShape)
{
  meshcheryakova::CompositeShape array;
  std::shared_ptr<meshcheryakova::Shape> shape = nullptr;
  BOOST_CHECK_THROW(array.addElement(shape), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_index_of_delete_compositeShape)
{
  meshcheryakova::CompositeShape array;
  BOOST_CHECK_THROW(array.deleteElement(5), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_coefficient_of_scale_composteShape)
{
  meshcheryakova::CompositeShape array(1);
  meshcheryakova::Circle circle{{2,3},5};
  std::shared_ptr<meshcheryakova::Shape> shape1 = std::make_shared<meshcheryakova::Circle>(circle);
  array.addElement(shape1);
  BOOST_CHECK_THROW(array.scale(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_correct_getArea_compositeShape)
{
  meshcheryakova::CompositeShape array(2);
  meshcheryakova::Circle circle{{2,3},4};
  meshcheryakova::Rectangle rectangle{2,5,{8,4}};
  std::shared_ptr<meshcheryakova::Shape> shape1 = std::make_shared<meshcheryakova::Circle>(circle);
  std::shared_ptr<meshcheryakova::Shape> shape2 = std::make_shared<meshcheryakova::Rectangle>(rectangle);
  array.addElement(shape1);
  array.addElement(shape2);

  BOOST_CHECK_CLOSE(circle.getArea() + rectangle.getArea(), array.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_correct_getFrameRect_compositeShape)
{
  meshcheryakova::CompositeShape array(2);
  meshcheryakova::Circle circle{{2,3},4};
  meshcheryakova::Rectangle rectangle{2,5,{8,4}};
  std::shared_ptr<meshcheryakova::Shape> shape1 = std::make_shared<meshcheryakova::Circle>(circle);
  std::shared_ptr<meshcheryakova::Shape> shape2 = std::make_shared<meshcheryakova::Rectangle>(rectangle);
  array.addElement(shape1);
  array.addElement(shape2);
  meshcheryakova::rectangle_t temp{11, 8, {3.5,3}};
  BOOST_CHECK_CLOSE(temp.width, array.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(temp.height, array.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(temp.pos.x, array.getFrameRect().pos.x, ACCURACY);
  BOOST_CHECK_CLOSE(temp.pos.y, array.getFrameRect().pos.y, ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_correct_scalling_compositeShape)
{
  meshcheryakova::CompositeShape array(2);
  meshcheryakova::Circle circle{{2,3},4};
  meshcheryakova::Rectangle rectangle{2,5,{8,4}};
  std::shared_ptr<meshcheryakova::Shape> shape1 = std::make_shared<meshcheryakova::Circle>(circle);
  std::shared_ptr<meshcheryakova::Shape> shape2 = std::make_shared<meshcheryakova::Rectangle>(rectangle);
  array.addElement(shape1);
  array.addElement(shape2);
  double full_area = array.getArea();
  double area_rec = rectangle.getArea();
  double  area_cir = circle.getArea();
  array.scale(1.5);
  BOOST_CHECK_CLOSE(full_area * 1.5 * 1.5, array.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(area_cir * 1.5 * 1.5, array[0]->getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(area_rec * 1.5 * 1.5, array[1]->getArea(), ACCURACY);
}
BOOST_AUTO_TEST_CASE(test_correct_moving_compositeShape)
{
  meshcheryakova::CompositeShape array(2);
  meshcheryakova::Circle circle{{2,3},4};
  meshcheryakova::Rectangle rectangle{2,5,{8,4}};
  std::shared_ptr<meshcheryakova::Shape> shape1 = std::make_shared<meshcheryakova::Circle>(circle);
  std::shared_ptr<meshcheryakova::Shape> shape2 = std::make_shared<meshcheryakova::Rectangle>(rectangle);
  array.addElement(shape1);
  array.addElement(shape2);
  double full_area = array.getArea();
  double area_rec = rectangle.getArea();
  double  area_cir = circle.getArea();
  meshcheryakova::point_t spot{3,4};
  array.move(spot);
  BOOST_CHECK_CLOSE(area_cir, circle.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(area_rec, rectangle.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(full_area, array.getArea(), ACCURACY);
  array.move(2,7.8);
  BOOST_CHECK_CLOSE(area_cir, circle.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(area_rec, rectangle.getArea(), ACCURACY);
  BOOST_CHECK_CLOSE(full_area, array.getArea(), ACCURACY);
}


