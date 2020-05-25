#define BOOST_TEST_MODULE shapetest

#include <cmath>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double ACCURACY_DOUBLE = 0.0001;

BOOST_AUTO_TEST_CASE(test_invalid_composite_operator)
{
  shabinsky::CompositeShape compositeShape;
  BOOST_CHECK_THROW(compositeShape[0], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_composite_addShape)
{
  shabinsky::CompositeShape compositeShape(10);
  BOOST_CHECK_THROW(compositeShape.addShape(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_composite_deleteShape)
{
  shabinsky::CompositeShape compositeShape;
  BOOST_CHECK_THROW(compositeShape.deleteShape(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_composite_scale)
{
  shabinsky::CompositeShape compositeShape;
  std::shared_ptr<shabinsky::Shape> rect1 = std::make_shared<shabinsky::Rectangle>(shabinsky::Rectangle({1, 1}, 2, 2));
  std::shared_ptr<shabinsky::Shape> rect2 = std::make_shared<shabinsky::Rectangle>(shabinsky::Rectangle({11, 1}, 2, 2));
  std::shared_ptr<shabinsky::Shape> rect3 = std::make_shared<shabinsky::Rectangle>(shabinsky::Rectangle({4, 5}, 2, 2));
  compositeShape.addShape(rect1);
  compositeShape.addShape(rect2);
  compositeShape.addShape(rect3);
  BOOST_CHECK_THROW(compositeShape.scale(-2), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_composite_create)
{
  shabinsky::CompositeShape compositeShape(10);
  BOOST_CHECK(compositeShape.getLength() == 10);
}

BOOST_AUTO_TEST_CASE(test_composite_addShape)
{
  shabinsky::CompositeShape compositeShape;
  std::shared_ptr<shabinsky::Shape> circle = std::make_shared<shabinsky::Circle>(shabinsky::Circle(1, {1, 1}));
  compositeShape.addShape(circle);
  BOOST_CHECK(compositeShape[0] == circle);
}

BOOST_AUTO_TEST_CASE(test_composite_deleteShape)
{
  shabinsky::CompositeShape compositeShape;
  std::shared_ptr<shabinsky::Shape> circle = std::make_shared<shabinsky::Circle>(shabinsky::Circle(1, {1, 1}));
  compositeShape.addShape(circle);
  BOOST_CHECK(compositeShape.getSize() == 1);
  compositeShape.deleteShape(0);
  BOOST_CHECK(compositeShape.getSize() == 0);
}

BOOST_AUTO_TEST_CASE(test_composite_getArea)
{
  shabinsky::CompositeShape compositeShape;
  std::shared_ptr<shabinsky::Shape> rect1 = std::make_shared<shabinsky::Rectangle>(shabinsky::Rectangle({1, 1}, 1, 1));
  std::shared_ptr<shabinsky::Shape> rect2 = std::make_shared<shabinsky::Rectangle>(shabinsky::Rectangle({1, 1}, 2, 2));
  std::shared_ptr<shabinsky::Shape> rect3 = std::make_shared<shabinsky::Rectangle>(shabinsky::Rectangle({1, 1}, 3, 3));
  compositeShape.addShape(rect1);
  compositeShape.addShape(rect2);
  compositeShape.addShape(rect3);
  BOOST_CHECK(compositeShape.getArea() == 14);
}

BOOST_AUTO_TEST_CASE(test_composite_getFrameRect)
{
  shabinsky::CompositeShape compositeShape;
  std::shared_ptr<shabinsky::Shape> rect1 = std::make_shared<shabinsky::Rectangle>(shabinsky::Rectangle({1, 1}, 2, 2));
  std::shared_ptr<shabinsky::Shape> rect2 = std::make_shared<shabinsky::Rectangle>(shabinsky::Rectangle({11, 1}, 2, 2));
  std::shared_ptr<shabinsky::Shape> rect3 = std::make_shared<shabinsky::Rectangle>(shabinsky::Rectangle({4, 5}, 2, 2));
  compositeShape.addShape(rect1);
  compositeShape.addShape(rect2);
  compositeShape.addShape(rect3);
  shabinsky::rectangle_t rectangle = compositeShape.getFrameRect();
  BOOST_CHECK(rectangle.height == 6);
  BOOST_CHECK(rectangle.width == 12);
  BOOST_CHECK(rectangle.pos.x = 6);
  BOOST_CHECK(rectangle.pos.y = 3);
}

BOOST_AUTO_TEST_CASE(test_composite_move_point)
{
  shabinsky::CompositeShape compositeShape;
  std::shared_ptr<shabinsky::Shape> rect1 = std::make_shared<shabinsky::Rectangle>(shabinsky::Rectangle({1, 1}, 2, 2));
  std::shared_ptr<shabinsky::Shape> rect2 = std::make_shared<shabinsky::Rectangle>(shabinsky::Rectangle({11, 1}, 2, 2));
  std::shared_ptr<shabinsky::Shape> rect3 = std::make_shared<shabinsky::Rectangle>(shabinsky::Rectangle({4, 5}, 2, 2));
  compositeShape.addShape(rect1);
  compositeShape.addShape(rect2);
  compositeShape.addShape(rect3);
  compositeShape.move({0, 0});
  for (int i = 0; i < 3; ++i)
  {
    BOOST_CHECK(compositeShape[i]->getFrameRect().pos.x == 0);
    BOOST_CHECK(compositeShape[i]->getFrameRect().pos.y == 0);
  }
}

BOOST_AUTO_TEST_CASE(test_composite_move)
{
  shabinsky::CompositeShape compositeShape;
  std::shared_ptr<shabinsky::Shape> rect1 = std::make_shared<shabinsky::Rectangle>(shabinsky::Rectangle({1, 1}, 2, 2));
  std::shared_ptr<shabinsky::Shape> rect2 = std::make_shared<shabinsky::Rectangle>(shabinsky::Rectangle({11, 1}, 2, 2));
  std::shared_ptr<shabinsky::Shape> rect3 = std::make_shared<shabinsky::Rectangle>(shabinsky::Rectangle({4, 5}, 2, 2));
  compositeShape.addShape(rect1);
  compositeShape.addShape(rect2);
  compositeShape.addShape(rect3);
  compositeShape.move(0, 1);
  BOOST_CHECK(compositeShape.getFrameRect().pos.x == 6);
  BOOST_CHECK(compositeShape.getFrameRect().pos.y == 4);
}

BOOST_AUTO_TEST_CASE(test_composite_scale)
{
  shabinsky::CompositeShape compositeShape;
  std::shared_ptr<shabinsky::Shape> rect1 = std::make_shared<shabinsky::Rectangle>(shabinsky::Rectangle({1, 1}, 2, 2));
  std::shared_ptr<shabinsky::Shape> rect2 = std::make_shared<shabinsky::Rectangle>(shabinsky::Rectangle({11, 1}, 2, 2));
  std::shared_ptr<shabinsky::Shape> rect3 = std::make_shared<shabinsky::Rectangle>(shabinsky::Rectangle({4, 5}, 2, 2));
  compositeShape.addShape(rect1);
  compositeShape.addShape(rect2);
  compositeShape.addShape(rect3);
  compositeShape.scale(2);
  shabinsky::rectangle_t rectangle = compositeShape.getFrameRect();
  std::cout << rectangle.height << " " << rectangle.width << "\n";
  BOOST_CHECK(rectangle.height == 8);
  BOOST_CHECK(rectangle.width == 14);
  BOOST_CHECK(rectangle.pos.x = 6);
  BOOST_CHECK(rectangle.pos.y = 3);
}
