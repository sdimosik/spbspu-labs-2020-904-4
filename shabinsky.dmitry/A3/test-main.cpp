#define BOOST_TEST_MODULE shapetest

#include <cmath>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double ACCURACY_DOUBLE = 0.0001;

BOOST_AUTO_TEST_CASE(test_invalid_argument_rectangle)
{
  BOOST_CHECK_THROW(shabinsky::Rectangle rect({75.0, 76.0}, -10.0, 13.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_rectangle_scale)
{
  shabinsky::Rectangle rect({75.0, 76.0}, 10.0, 13.0);
  BOOST_CHECK_THROW(rect.scale(-1.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_permanency_move_rectange)
{
  shabinsky::Rectangle rect({75.0, 76.0}, 10.0, 13.0);
  const shabinsky::rectangle_t frameRect = rect.getFrameRect();
  const double area = rect.getArea();
  rect.move({10.0, 10.0});
  BOOST_CHECK_CLOSE(frameRect.height, rect.getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.width, rect.getFrameRect().width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(area, rect.getArea(), ACCURACY_DOUBLE);
  rect.move(10.0, 10.0);
  BOOST_CHECK_CLOSE(frameRect.height, rect.getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.width, rect.getFrameRect().width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(area, rect.getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_correct_move_rectangle)
{
  shabinsky::Rectangle rect({75.0, 76.0}, 10.0, 13.0);
  const double x = -85.0,
    y = 10.0,
    oldX = rect.getPosition().x,
    oldY = rect.getPosition().y;
  rect.move(x, y);
  BOOST_CHECK_CLOSE(rect.getPosition().x, x + oldX, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rect.getPosition().y, y + oldY, ACCURACY_DOUBLE);
  rect.move({x, y});
  BOOST_CHECK_CLOSE(rect.getPosition().x, x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rect.getPosition().y, y, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_scale_rectangle_area)
{
  shabinsky::Rectangle rect({75.0, 76.0}, 10.0, 13.0);
  const double area_rect = rect.getArea(),
    scale = 1.5;
  rect.scale(scale);
  BOOST_CHECK_CLOSE(area_rect * scale * scale, rect.getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_circle)
{
  BOOST_CHECK_THROW(shabinsky::Circle circle(-13.0, {75.0, 76.0}), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_circle_scale)
{
  shabinsky::Circle circle(13.0, {75.0, 76.0});
  BOOST_CHECK_THROW(circle.scale(-1.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_permanency_move_circle)
{
  shabinsky::Circle circle(13.0, {75.0, 76.0});
  const shabinsky::rectangle_t frameRect = circle.getFrameRect();
  const double area = circle.getArea();
  circle.move({10.0, 10.0});
  BOOST_CHECK_CLOSE(frameRect.height, circle.getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.width, circle.getFrameRect().width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(area, circle.getArea(), ACCURACY_DOUBLE);
  circle.move(10, 10);
  BOOST_CHECK_CLOSE(frameRect.height, circle.getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.width, circle.getFrameRect().width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(area, circle.getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_correct_move_circle)
{
  shabinsky::Circle circle(13.0, {75.0, 76.0});
  const double x = -85.0,
    y = 10.0,
    oldX = circle.getPosition().x,
    oldY = circle.getPosition().y;
  circle.move(x, y);
  BOOST_CHECK_CLOSE(circle.getPosition().x, x + oldX, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle.getPosition().y, y + oldY, ACCURACY_DOUBLE);
  circle.move({x, y});
  BOOST_CHECK_CLOSE(circle.getPosition().x, x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle.getPosition().y, y, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_scale_circle_area)
{
  shabinsky::Circle circle(13.0, {75.0, 76.0});
  const double area_circle = circle.getArea(),
    scale = 5.0;
  circle.scale(scale);
  BOOST_CHECK_CLOSE(area_circle * scale * scale, circle.getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_invalid_composite_create)
{
  BOOST_CHECK_THROW(shabinsky::CompositeShape compositeShape(-5), std::bad_alloc);
}

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
