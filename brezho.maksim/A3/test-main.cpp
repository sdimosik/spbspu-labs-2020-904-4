#define BOOST_TEST_MODULE mytest

#include <memory>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"

const double PERMISSIBLE_ACCURACY = 0.0001;

BOOST_AUTO_TEST_CASE(test_invalid_argument_scaling_coefficient_composite_shape)
{
  brezho::CompositeShape shapes;
  brezho::Triangle triangle({ 3.0, 4.0 }, { 0.0, 4.0 }, { 3.0, 0.0 });
  brezho::Rectangle rect({ 3.0, 1.0 }, 2.0, 2.0);
  brezho::Circle circle({ 1.0, 4.0 }, 0.5);
  std::shared_ptr<brezho::Shape> rect1 = std::make_shared<brezho::Rectangle>(rect);
  std::shared_ptr<brezho::Shape> circle1 = std::make_shared<brezho::Circle>(circle);
  std::shared_ptr<brezho::Shape> triangle1 = std::make_shared<brezho::Triangle>(triangle);
  shapes.addShape(rect1);
  shapes.addShape(circle1);
  shapes.addShape(triangle1);
  int coeff = -1;
  BOOST_CHECK_THROW(shapes.scale(coeff), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_index_empty_array_composite_shape)
{
  brezho::CompositeShape shapes;
  BOOST_CHECK_THROW(shapes[0], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_too_big_index_composite_shape)
{
  brezho::CompositeShape shapes;
  brezho::Triangle triangle({ 3.0, 4.0 }, { 0.0, 4.0 }, { 3.0, 0.0 });
  brezho::Rectangle rect({ 3.0, 1.0 }, 2.0, 2.0);
  brezho::Circle circle({ 1.0, 4.0 }, 0.5);
  std::shared_ptr<brezho::Shape> rect1 = std::make_shared<brezho::Rectangle>(rect);
  std::shared_ptr<brezho::Shape> circle1 = std::make_shared<brezho::Circle>(circle);
  std::shared_ptr<brezho::Shape> triangle1 = std::make_shared<brezho::Triangle>(triangle);
  shapes.addShape(rect1);
  shapes.addShape(circle1);
  shapes.addShape(triangle1);
  BOOST_CHECK_THROW(shapes[5], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_add_shape_composite_shape)
{
  brezho::CompositeShape shapes;
  std::shared_ptr<brezho::Shape> ptr = nullptr;
  BOOST_CHECK_THROW(shapes.addShape(ptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_index_empty_array_delete_composite_shape)
{
  brezho::CompositeShape shapes;
  BOOST_CHECK_THROW(shapes.deleteShape(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_too_big_index_delete_composite_shape)
{
  brezho::CompositeShape shapes;
  brezho::Triangle triangle({ 3.0, 4.0 }, { 0.0, 4.0 }, { 3.0, 0.0 });
  brezho::Rectangle rect({ 3.0, 1.0 }, 2.0, 2.0);
  brezho::Circle circle({ 1.0, 4.0 }, 0.5);
  std::shared_ptr<brezho::Shape> rect1 = std::make_shared<brezho::Rectangle>(rect);
  std::shared_ptr<brezho::Shape> circle1 = std::make_shared<brezho::Circle>(circle);
  std::shared_ptr<brezho::Shape> triangle1 = std::make_shared<brezho::Triangle>(triangle);
  shapes.addShape(rect1);
  shapes.addShape(circle1);
  shapes.addShape(triangle1);
  BOOST_CHECK_THROW(shapes.deleteShape(5), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_add_shape_composite_shape)
{
  brezho::CompositeShape shapes;
  brezho::Triangle triangle({ 3.0, 4.0 }, { 0.0, 4.0 }, { 3.0, 0.0 });
  std::shared_ptr<brezho::Shape> triangle1 = std::make_shared<brezho::Triangle>(triangle);
  shapes.addShape(triangle1);
  BOOST_CHECK(shapes[0] == triangle1);
}

BOOST_AUTO_TEST_CASE(test_delete_shape_composite_shape)
{
  brezho::CompositeShape shapes;
  brezho::Triangle triangle({ 3.0, 4.0 }, { 0.0, 4.0 }, { 3.0, 0.0 });
  std::shared_ptr<brezho::Shape> triangle1 = std::make_shared<brezho::Triangle>(triangle);
  shapes.addShape(triangle1);
  BOOST_CHECK(shapes.getUsedSize() == 1);
  shapes.deleteShape(0);
  BOOST_CHECK(shapes.getUsedSize() == 0);
}

BOOST_AUTO_TEST_CASE(test_get_full_size_composite_shape)
{
  const int fullSize = 10;
  brezho::CompositeShape shapes(fullSize);
  BOOST_CHECK(shapes.getFullSize() == fullSize);
}

BOOST_AUTO_TEST_CASE(test_get_used_size_composite_shape)
{
  brezho::CompositeShape shapes;
  brezho::Triangle triangle({ 3.0, 4.0 }, { 0.0, 4.0 }, { 3.0, 0.0 });
  std::shared_ptr<brezho::Shape> triangle1 = std::make_shared<brezho::Triangle>(triangle);
  shapes.addShape(triangle1);
  BOOST_CHECK(shapes.getUsedSize() == 1);
}

BOOST_AUTO_TEST_CASE(test_get_frame_rect_composite_shape)
{
  brezho::CompositeShape shapes;
  brezho::Triangle triangle({ 4.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 3.0 });
  brezho::Rectangle rect({ 4.0, 2.0 }, 2, 2);
  brezho::Circle circle({ 1.0, 4.0 }, 1);
  std::shared_ptr<brezho::Shape> rect1 = std::make_shared<brezho::Rectangle>(rect);
  std::shared_ptr<brezho::Shape> circle1 = std::make_shared<brezho::Circle>(circle);
  std::shared_ptr<brezho::Shape> triangle1 = std::make_shared<brezho::Triangle>(triangle);
  shapes.addShape(rect1);
  shapes.addShape(circle1);
  shapes.addShape(triangle1);
  const double height = 5.0,
    width = 5.0;
  BOOST_CHECK_CLOSE(shapes.getFrameRect().height, height, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().width, width, PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_get_area_composite_shape)
{
  brezho::CompositeShape shapes;
  brezho::Triangle triangle({ 3.0, 4.0 }, { 0.0, 4.0 }, { 3.0, 0.0 });
  brezho::Rectangle rect({ 3.0, 1.0 }, 2.0, 2.0);
  brezho::Circle circle({ 1.0, 4.0 }, 0.5);
  std::shared_ptr<brezho::Shape> rect1 = std::make_shared<brezho::Rectangle>(rect);
  std::shared_ptr<brezho::Shape> circle1 = std::make_shared<brezho::Circle>(circle);
  std::shared_ptr<brezho::Shape> triangle1 = std::make_shared<brezho::Triangle>(triangle);
  shapes.addShape(rect1);
  shapes.addShape(circle1);
  shapes.addShape(triangle1);
  const double sumArea = rect.getArea() + circle.getArea() + triangle.getArea();
  BOOST_CHECK_CLOSE(shapes.getArea(), sumArea, PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_move_composite_shape)
{
  brezho::CompositeShape shapes;
  brezho::Triangle triangle({ 4.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 3.0 });
  brezho::Rectangle rect({ 4.0, 2.0 }, 2, 2);
  brezho::Circle circle({ 1.0, 4.0 }, 1);
  std::shared_ptr<brezho::Shape> rect1 = std::make_shared<brezho::Rectangle>(rect);
  std::shared_ptr<brezho::Shape> circle1 = std::make_shared<brezho::Circle>(circle);
  std::shared_ptr<brezho::Shape> triangle1 = std::make_shared<brezho::Triangle>(triangle);
  shapes.addShape(rect1);
  shapes.addShape(circle1);
  shapes.addShape(triangle1);
  const double x = 8,
    y = 8,
    rectOldX = rect.getPosition().x,
    rectOldY = rect.getPosition().y,
    circleOldX = circle.getPosition().x,
    circleOldY = circle.getPosition().y,
    triangleOldX = triangle.getPosition().x,
    triangleOldY = triangle.getPosition().y,
    shapesX = shapes.getPosition().x,
    shapesY = shapes.getPosition().y,
    height = 5.0,
    width = 5.0;
  shapes.move(x, y);
  BOOST_CHECK_CLOSE(rect1->getPosition().x, x + rectOldX, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(rect1->getPosition().y, y + rectOldY, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(circle1->getPosition().x, x + circleOldX, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(circle1->getPosition().y, y + circleOldY, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(triangle1->getPosition().x, x + triangleOldX, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(triangle1->getPosition().y, y + triangleOldY, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().width, width, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().height, height, PERMISSIBLE_ACCURACY);
  brezho::point_t point{ 3.4, 3.4 };
  shapes.move(point);
  BOOST_CHECK_CLOSE(rect1->getPosition().x, point.x + rectOldX - shapesX, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(rect1->getPosition().y, point.y + rectOldY - shapesY, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(circle1->getPosition().x, point.x + circleOldX - shapesX, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(circle1->getPosition().y, point.y + circleOldY - shapesY, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(triangle1->getPosition().x, point.x + triangleOldX - shapesX, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(triangle1->getPosition().y, point.y + triangleOldY - shapesY, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().width, width, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().height, height, PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_scale_composite_shape)
{
  brezho::CompositeShape shapes;
  brezho::Triangle triangle({ 4.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 3.0 });
  brezho::Rectangle rect({ 3, 1 }, 2, 2);
  brezho::Circle circle({ 1, 4 }, 0.5);
  std::shared_ptr<brezho::Shape> rect1 = std::make_shared<brezho::Rectangle>(rect);
  std::shared_ptr<brezho::Shape> circle1 = std::make_shared<brezho::Circle>(circle);
  std::shared_ptr<brezho::Shape> triangle1 = std::make_shared<brezho::Triangle>(triangle);
  shapes.addShape(rect1);
  shapes.addShape(circle1);
  shapes.addShape(triangle1);
  const double rectArea = rect.getArea(),
    circleArea = circle.getArea(),
    triangleArea = triangle.getArea(),
    scale = 0.5;
  shapes.scale(scale);
  BOOST_CHECK_CLOSE(rectArea * scale * scale, rect1->getArea(), PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(circleArea * scale * scale, circle1->getArea(), PERMISSIBLE_ACCURACY);
  BOOST_CHECK_CLOSE(triangleArea * scale * scale, triangle1->getArea(), PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_copy_composite_shape)
{
  brezho::CompositeShape shapes;
  brezho::Triangle triangle({ 4.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 3.0 });
  std::shared_ptr<brezho::Shape> triangle1 = std::make_shared<brezho::Triangle>(triangle);
  shapes.addShape(triangle1);
  brezho::CompositeShape shapes1 = shapes;
  BOOST_CHECK_CLOSE(shapes1[0]->getArea(), shapes[0]->getArea(), PERMISSIBLE_ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_semantics_move_composite_shape)
{
  brezho::CompositeShape shapes;
  brezho::Triangle triangle({ 4.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 3.0 });
  std::shared_ptr<brezho::Shape> triangle1 = std::make_shared<brezho::Triangle>(triangle);
  shapes.addShape(triangle1);
  const double areaCircle = triangle.getArea();
  brezho::CompositeShape shapes1(std::move(shapes));
  BOOST_CHECK_CLOSE(shapes1[0]->getArea(), areaCircle, PERMISSIBLE_ACCURACY);
  BOOST_CHECK_THROW(shapes[0], std::out_of_range);
}
