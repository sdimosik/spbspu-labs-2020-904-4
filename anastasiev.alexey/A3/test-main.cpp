#define BOOST_TEST_MODULE tests

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"

const double ACCURACY = 0.001;

BOOST_AUTO_TEST_CASE(test_compositeShape_index_operator)
{
  anastasiev::CompositeShape compShape;
  BOOST_CHECK_THROW(compShape[-1], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_compositeShape_add_nullptr_shape)
{
  anastasiev::CompositeShape compShape;
  BOOST_CHECK_THROW(compShape.add(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_compositeShape_remove_invalid_index)
{
  anastasiev::CompositeShape compShape;
  BOOST_CHECK_THROW(compShape.remove(-1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_compositeShape_scale_invalid_factor)
{
  anastasiev::CompositeShape compShape;
  BOOST_CHECK_THROW(compShape.scale(-50.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_compositeShape_correct_copy_constructor)
{
  std::shared_ptr<anastasiev::Shape> rect1
      = std::make_shared<anastasiev::Rectangle>(anastasiev::Rectangle(3.0, 5.0, {0.0, 0.0})),
      rect2 = std::make_shared<anastasiev::Rectangle>(anastasiev::Rectangle(3.0, 3.0, {5.0, 5.0}));
  anastasiev::CompositeShape compShape1;
  compShape1.add(rect1);
  compShape1.add(rect2);
  anastasiev::CompositeShape compShape2(compShape1);
  BOOST_CHECK_CLOSE(compShape1.getArea(), compShape2.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_compositeShape_correct_move_constructor)
{
  std::shared_ptr<anastasiev::Shape> rect1
      = std::make_shared<anastasiev::Rectangle>(anastasiev::Rectangle(3.0, 5.0, {0.0, 0.0})),
      rect2 = std::make_shared<anastasiev::Rectangle>(anastasiev::Rectangle(3.0, 3.0, {5.0, 5.0}));
  anastasiev::CompositeShape compShape1;
  compShape1.add(rect1);
  compShape1.add(rect2);
  const double area = compShape1.getArea();
  anastasiev::CompositeShape compShape2(std::move(compShape1));
  BOOST_CHECK_CLOSE(area, compShape2.getArea(), ACCURACY);
  BOOST_CHECK_THROW(compShape1[0],std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_compositeShape_correct_assignment_operator)
{
  std::shared_ptr<anastasiev::Shape> rect1
      = std::make_shared<anastasiev::Rectangle>(anastasiev::Rectangle(3.0, 5.0, {0.0, 0.0})),
      rect2 = std::make_shared<anastasiev::Rectangle>(anastasiev::Rectangle(3.0, 3.0, {5.0, 5.0}));
  anastasiev::CompositeShape compShape1;
  compShape1.add(rect1);
  compShape1.add(rect2);
  anastasiev::CompositeShape compShape2 = compShape1;
  BOOST_CHECK_CLOSE(compShape1.getArea(), compShape2.getArea(), ACCURACY);
}


BOOST_AUTO_TEST_CASE(test_compositeShape_correct_moving_operator)
{
  std::shared_ptr<anastasiev::Shape> rect1
      = std::make_shared<anastasiev::Rectangle>(anastasiev::Rectangle(3.0, 5.0, {0.0, 0.0})),
      rect2 = std::make_shared<anastasiev::Rectangle>(anastasiev::Rectangle(3.0, 3.0, {5.0, 5.0}));
  anastasiev::CompositeShape compShape1;
  compShape1.add(rect1);
  compShape1.add(rect2);
  const double area = compShape1.getArea();
  anastasiev::CompositeShape compShape2 = std::move(compShape1);
  BOOST_CHECK_CLOSE(area, compShape2.getArea(), ACCURACY);
  BOOST_CHECK_THROW(compShape1[0],std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_compositeShape_scale_area)
{
  const double factor = 1.5;
  std::shared_ptr<anastasiev::Shape> rect1
      = std::make_shared<anastasiev::Rectangle>(anastasiev::Rectangle(3.0, 5.0, {0.0, 0.0})),
      rect2 = std::make_shared<anastasiev::Rectangle>(anastasiev::Rectangle(3.0, 3.0, {5.0, 5.0}));
  anastasiev::CompositeShape compShape;
  compShape.add(rect1);
  compShape.add(rect2);
  const double area = compShape.getArea();
  compShape.scale(factor);
  BOOST_CHECK_CLOSE(area * factor * factor, compShape.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_compositeShape_move_area_constancy)
{
  std::shared_ptr<anastasiev::Shape> rect
      = std::make_shared<anastasiev::Rectangle>(anastasiev::Rectangle(3.0, 5.0, {0.0, 0.0})),
    circle = std::make_shared<anastasiev::Circle>(anastasiev::Circle(3.0, {3.0, 0.0}));
  anastasiev::CompositeShape compShape;
  compShape.add(rect);
  compShape.add(circle);
  const double dx = 3.0,
    dy = 2.0,
    area = compShape.getArea();
    
  compShape.move(dx, dy);
  BOOST_CHECK_CLOSE(area, compShape.getArea(), ACCURACY);
  compShape.move({dx, dy});
  BOOST_CHECK_CLOSE(area, compShape.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_compositeShape_correct_frame)
{
  std::shared_ptr<anastasiev::Shape> rect1
      = std::make_shared<anastasiev::Rectangle>(anastasiev::Rectangle(3.0, 5.0, {0.0, 0.0})),
      rect2 = std::make_shared<anastasiev::Rectangle>(anastasiev::Rectangle(3.0, 3.0, {0.0, 4.0}));
  anastasiev::CompositeShape compShape;
  compShape.add(rect1);
  compShape.add(rect2);
  const double width = 3.0,
      height = 8.0;
  BOOST_CHECK_CLOSE(width, compShape.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(height, compShape.getFrameRect().height, ACCURACY);
}
