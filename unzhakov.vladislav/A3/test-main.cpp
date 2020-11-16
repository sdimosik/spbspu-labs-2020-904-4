#define BOOST_TEST_MODULE MY_TEST

#include <cmath>
#include <memory>

#include <boost/test/included/unit_test.hpp>
#include "../common/circle.hpp"
#include "../common/rectangle.hpp"
#include "../common/triangle.hpp"
#include "../common/composite-shape.hpp"

BOOST_AUTO_TEST_SUITE(circle_test)

  const double EPSILON = 0.000001;
  const double RADIUS = 3.0;
  const double COEFFICIENT = 2.0;
  const unzhakov::point_t CENTER = {1.5, 2.6};
  const unzhakov::point_t MOVE_POINT = {4.3, 5.2};
  const double DX = 5.5;
  const double DY = 6.0;
  const double AREA = M_PI * RADIUS * RADIUS;

  BOOST_AUTO_TEST_CASE(circle_and_frame_data_after_moving_on_axes)
  {
    unzhakov::Circle circle(RADIUS, CENTER);
    const double frameHeight = circle.getFrameRect().height;
    const double frameWidth = circle.getFrameRect().width;
    circle.move(DX, DY);
    BOOST_CHECK_CLOSE(circle.getArea(), AREA, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, frameHeight, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, frameWidth, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(circle_and_frame_data_after_moving_in_point)
  {
    unzhakov::Circle circle(RADIUS, CENTER);
    const double frameHeight = circle.getFrameRect().height;
    const double frameWidth = circle.getFrameRect().width;
    circle.move(MOVE_POINT);
    BOOST_CHECK_CLOSE(circle.getArea(), AREA, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, frameHeight, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, frameWidth, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(circle_and_frame_data_after_scaling)
  {
    unzhakov::Circle circle(RADIUS, CENTER);
    circle.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(circle.getArea(), AREA * COEFFICIENT * COEFFICIENT, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(circle_invalid_radius)
  {
    BOOST_CHECK_THROW(unzhakov::Circle circle(0.0, CENTER), std::invalid_argument);
    BOOST_CHECK_THROW(unzhakov::Circle circle(-RADIUS, CENTER), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(circle_invalid_scale_coefficient)
  {
    unzhakov::Circle circle(RADIUS, CENTER);
    BOOST_CHECK_THROW(circle.scale(0.0), std::invalid_argument);
    BOOST_CHECK_THROW(circle.scale(-COEFFICIENT), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(rectangle_test)

  const double EPSILON = 0.000001;
  const double WIDTH = 10.0;
  const double HEIGHT = 15.0;
  const double COEFFICIENT = 2.0;
  const unzhakov::point_t CENTER = {1.5, 2.6};
  const unzhakov::point_t MOVE_POINT = {4.3, 5.2};
  const double DX = 5.5;
  const double DY = 6.0;
  const double AREA = WIDTH * HEIGHT;

  BOOST_AUTO_TEST_CASE(rectangle_and_frame_data_after_moving_on_axes)
  {
    unzhakov::Rectangle rectangle(WIDTH, HEIGHT, CENTER);
    const double frameWidth = rectangle.getFrameRect().width;
    const double frameHeight = rectangle.getFrameRect().height;
    rectangle.move(DX, DY);
    BOOST_CHECK_CLOSE(rectangle.getArea(), AREA, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, frameWidth, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, frameHeight, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectangle_and_frame_data_after_moving_in_point)
  {
    unzhakov::Rectangle rectangle(WIDTH, HEIGHT, CENTER);
    const double frameWidth = rectangle.getFrameRect().width;
    const double frameHeight = rectangle.getFrameRect().height;
    rectangle.move(MOVE_POINT);
    BOOST_CHECK_CLOSE(rectangle.getArea(), AREA, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, frameWidth, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, frameHeight, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectangle_and_frame_data_after_scaling)
  {
    unzhakov::Rectangle rectangle(WIDTH, HEIGHT, CENTER);
    rectangle.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(rectangle.getArea(), AREA * COEFFICIENT * COEFFICIENT, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectangle_invalid_scale_coefficient)
  {
    unzhakov::Rectangle rectangle(WIDTH, HEIGHT, CENTER);
    BOOST_CHECK_THROW(rectangle.scale(0.0), std::invalid_argument);
    BOOST_CHECK_THROW(rectangle.scale(-COEFFICIENT), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(rectangle_invalid_width)
  {
    BOOST_CHECK_THROW(unzhakov::Rectangle rectangle(0.0, HEIGHT, CENTER), std::invalid_argument);
    BOOST_CHECK_THROW(unzhakov::Rectangle rectangle(-WIDTH, HEIGHT, CENTER), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(rectangle_invalid_height)
  {
    BOOST_CHECK_THROW(unzhakov::Rectangle rectangle(WIDTH, 0.0, CENTER), std::invalid_argument);
    BOOST_CHECK_THROW(unzhakov::Rectangle rectangle(WIDTH, -HEIGHT, CENTER), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(triangle_test)

  const double EPSILON = 0.000001;
  const unzhakov::point_t VERTEX1 = {12, 11};
  const unzhakov::point_t VERTEX2 = {15, 15};
  const unzhakov::point_t VERTEX3 = {18, 11};
  const double COEFFICIENT = 2.0;
  const unzhakov::point_t MOVE_POINT = {4.3, 5.2};
  const double DX = 5.5;
  const double DY = 6.0;
//const double AREA = 12;

  BOOST_AUTO_TEST_CASE(triangle_and_frame_data_after_moving_on_axes)
  {
    unzhakov::Triangle triangle(VERTEX1, VERTEX2, VERTEX3);
    const double frameWidth = triangle.getFrameRect().width;
    const double frameHeight = triangle.getFrameRect().height;
    const double area = triangle.getArea();
    triangle.move(DX, DY);
    BOOST_CHECK_CLOSE(triangle.getArea(), area, EPSILON);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, frameWidth, EPSILON);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, frameHeight, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectangle_and_frame_data_after_moving_in_point)
  {
    unzhakov::Triangle triangle(VERTEX1, VERTEX2, VERTEX3);
    const double frameWidth = triangle.getFrameRect().width;
    const double frameHeight = triangle.getFrameRect().height;
    const double area = triangle.getArea();
    triangle.move(MOVE_POINT);
    BOOST_CHECK_CLOSE(triangle.getArea(), area, EPSILON);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, frameWidth, EPSILON);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, frameHeight, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectangle_and_frame_data_after_scaling)
  {
    unzhakov::Triangle triangle(VERTEX1, VERTEX2, VERTEX3);
    const double area = triangle.getArea();
    triangle.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(triangle.getArea(), area * COEFFICIENT * COEFFICIENT, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(triangle_invalid_scale_coefficient)
  {
    unzhakov::Triangle triangle(VERTEX1, VERTEX2, VERTEX3);
    BOOST_CHECK_THROW(triangle.scale(0.0), std::invalid_argument);
    BOOST_CHECK_THROW(triangle.scale(-COEFFICIENT), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(compositeShape_test)

  const double EPSILON = 0.000001;
  const double RADIUS = 6.8;
  const double WIDTH = 6.6;
  const double HEIGHT = 4.4;
  const unzhakov::point_t CENTRE = {4.6, -4.5};
  const unzhakov::point_t CENTRE1 = {9.1, 67.8};
  const unzhakov::point_t POINT = {-8.1, 3.2};
  const double DX = 5.8;
  const double DY = 12.56;
  const double COEFFICIENT = 5.0;
  const double INVALID_COEFFICIENT = -0.56;

  BOOST_AUTO_TEST_CASE(compositeShape_correct_add)
  {
    std::shared_ptr<unzhakov::Rectangle> rect = std::make_shared<unzhakov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    std::shared_ptr<unzhakov::Circle> circle = std::make_shared<unzhakov::Circle>(RADIUS, CENTRE);
    unzhakov::CompositeShape array;
    array.add(circle);
    array.add(rect);
    BOOST_CHECK_EQUAL(array.getSize(), 2);
    BOOST_CHECK_EQUAL(array[0], circle);
    BOOST_CHECK_EQUAL(array[1], rect);
  }

  BOOST_AUTO_TEST_CASE(compositeShape_incorrect_add)
  {
    std::shared_ptr<unzhakov::Rectangle> rect = std::make_shared<unzhakov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    unzhakov::CompositeShape array;
    array.add(rect);
    BOOST_CHECK_THROW(array.add(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(compositeShape_add_compositeShape)
  {
    std::shared_ptr<unzhakov::Rectangle> rect = std::make_shared<unzhakov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    std::shared_ptr<unzhakov::Circle> circle = std::make_shared<unzhakov::Circle>(RADIUS, CENTRE);
    std::shared_ptr<unzhakov::Circle> circle1 = std::make_shared<unzhakov::Circle>(RADIUS, CENTRE1);
    unzhakov::CompositeShape array;
    std::shared_ptr<unzhakov::CompositeShape> array1 = std::make_shared<unzhakov::CompositeShape>();
    array.add(circle);
    array.add(rect);
    array.add(array1);
    BOOST_CHECK_EQUAL(array[0], circle);
    BOOST_CHECK_EQUAL(array[1], rect);
    BOOST_CHECK_EQUAL(array[2], array1);
  }

  BOOST_AUTO_TEST_CASE(compositeShape_remove)
  {
    std::shared_ptr<unzhakov::Rectangle> rect = std::make_shared<unzhakov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    std::shared_ptr<unzhakov::Circle> circle = std::make_shared<unzhakov::Circle>(RADIUS, CENTRE);
    std::shared_ptr<unzhakov::Circle> circle1 = std::make_shared<unzhakov::Circle>(RADIUS, CENTRE1);
    unzhakov::CompositeShape array;
    array.add(circle);
    array.add(rect);
    array.add(circle1);
    array.remove(1);
    BOOST_CHECK_EQUAL(array.getSize(), 2);
    BOOST_CHECK_EQUAL(array[0], circle);
    BOOST_CHECK_EQUAL(array[1], circle1);
  }

  BOOST_AUTO_TEST_CASE(compositeShape_invalid_remove)
  {
    std::shared_ptr<unzhakov::Rectangle> rect = std::make_shared<unzhakov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    std::shared_ptr<unzhakov::Circle> circle = std::make_shared<unzhakov::Circle>(RADIUS, CENTRE);
    unzhakov::CompositeShape array;
    array.add(circle);
    array.add(rect);
    BOOST_CHECK_THROW(array.remove(array.getSize()), std::out_of_range);
    BOOST_CHECK_THROW(array.remove(10), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(compositeShape_remove_delete_last_element)
  {
    std::shared_ptr<unzhakov::Circle> circle = std::make_shared<unzhakov::Circle>(RADIUS, CENTRE);
    unzhakov::CompositeShape array;
    array.add(circle);
    BOOST_CHECK_NO_THROW(array.remove(0));
  }


  BOOST_AUTO_TEST_CASE(compositeShape_area_move_on_rect)
  {
    std::shared_ptr<unzhakov::Rectangle> rect = std::make_shared<unzhakov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    std::shared_ptr<unzhakov::Circle> circle = std::make_shared<unzhakov::Circle>(RADIUS, CENTRE1);
    unzhakov::CompositeShape array;
    array.add(circle);
    array.add(rect);
    const double area = array.getArea();

    array.move(DX, DY);
    BOOST_CHECK_EQUAL(array[0], circle);
    BOOST_CHECK_EQUAL(array[1], rect);
    BOOST_CHECK_EQUAL(array.getSize(), 2);
    BOOST_CHECK_CLOSE(array.getArea(), area, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(compositeShape_scale_correct_coefficient)
  {
    std::shared_ptr<unzhakov::Rectangle> rect = std::make_shared<unzhakov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    std::shared_ptr<unzhakov::Circle> circle = std::make_shared<unzhakov::Circle>(RADIUS, CENTRE1);
    unzhakov::CompositeShape array;
    array.add(circle);
    array.add(rect);
    const double area = array.getArea();
    const unzhakov::point_t centre = array.getCenter();
    array.scale(COEFFICIENT);

    BOOST_CHECK_EQUAL(array[0], circle);
    BOOST_CHECK_EQUAL(array[1], rect);
    BOOST_CHECK_CLOSE(centre.x, array.getCenter().x, EPSILON);
    BOOST_CHECK_CLOSE(centre.y, array.getCenter().y, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().width, 73, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().height, 406.5, EPSILON);
    BOOST_CHECK_EQUAL(array.getSize(), 2);
    BOOST_CHECK_CLOSE(array.getArea(), area * COEFFICIENT * COEFFICIENT, EPSILON);
    BOOST_CHECK_CLOSE(array[0]->getArea(), M_PI * RADIUS * RADIUS * COEFFICIENT * COEFFICIENT, EPSILON);
    BOOST_CHECK_CLOSE(array[0]->getCenter().x, (CENTRE1.x - centre.x) * COEFFICIENT + centre.x, EPSILON);
    BOOST_CHECK_CLOSE(array[0]->getCenter().y, (CENTRE1.y - centre.y) * COEFFICIENT + centre.y, EPSILON);
    BOOST_CHECK_CLOSE(array[1]->getArea(), WIDTH * HEIGHT * COEFFICIENT * COEFFICIENT, EPSILON);
    BOOST_CHECK_CLOSE(array[1]->getCenter().x, (CENTRE.x - centre.x) * COEFFICIENT + centre.x, EPSILON);
    BOOST_CHECK_CLOSE(array[1]->getCenter().y, (CENTRE.y - centre.y) * COEFFICIENT + centre.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(compositeShape_scale_incorrect_coefficient)
  {
    std::shared_ptr<unzhakov::Circle> circle = std::make_shared<unzhakov::Circle>(RADIUS, CENTRE);
    unzhakov::CompositeShape array;
    array.add(circle);
    BOOST_CHECK_THROW(array.scale(INVALID_COEFFICIENT), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(compositeShape_scale_zero_as_coefficient)
  {
    std::shared_ptr<unzhakov::Circle> circle = std::make_shared<unzhakov::Circle>(RADIUS, CENTRE);
    unzhakov::CompositeShape array;
    array.add(circle);
    BOOST_CHECK_THROW(array.scale(0.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(compositeShape_incorrect_indexing)
  {
    std::shared_ptr<unzhakov::Rectangle> rect = std::make_shared<unzhakov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    std::shared_ptr<unzhakov::Circle> circle = std::make_shared<unzhakov::Circle>(RADIUS, CENTRE1);
    unzhakov::CompositeShape array;
    array.add(circle);
    array.add(rect);
    BOOST_CHECK_THROW(array[array.getSize()], std::out_of_range);
    BOOST_CHECK_THROW(array[4], std::out_of_range);
    BOOST_CHECK_THROW(array[15], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(compositeShape_move_empty_composite)
  {
    std::shared_ptr<unzhakov::Rectangle> rect = std::make_shared<unzhakov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    std::shared_ptr<unzhakov::Circle> circle = std::make_shared<unzhakov::Circle>(RADIUS, CENTRE1);
    unzhakov::CompositeShape array;
    array.add(circle);
    unzhakov::CompositeShape array1;
    array1 = std::move(array);
    BOOST_CHECK_THROW(array.remove(0), std::logic_error);
    BOOST_CHECK_CLOSE(array.getArea(), 0.0, EPSILON);
    BOOST_CHECK_EQUAL(array.getSize(), 0);
    BOOST_CHECK_CLOSE(array.getCenter().x, 0.0, EPSILON);
    BOOST_CHECK_CLOSE(array.getCenter().x, 0.0, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().height, -1.0, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().width, -1.0, EPSILON);
    BOOST_CHECK_NO_THROW(array.move(DX, DY));
    BOOST_CHECK_NO_THROW(array.move(POINT));
    BOOST_CHECK_NO_THROW(array.printData());
    BOOST_CHECK_NO_THROW(array.scale(COEFFICIENT));
  }

  BOOST_AUTO_TEST_CASE(compositeShape_copy_empty_composite)
  {
    unzhakov::CompositeShape array;
    array.add(std::make_shared<unzhakov::Circle>(3.0, unzhakov::point_t{5.0, 4.3}));
    unzhakov::CompositeShape array1(std::move(array));
    BOOST_CHECK_NO_THROW(array.add(std::make_shared<unzhakov::Circle>(2.5, unzhakov::point_t{1.0, 1.0})));
    array.remove(0);
    BOOST_CHECK_THROW(array.remove(0), std::logic_error);
    BOOST_CHECK_CLOSE(array.getArea(), 0.0, EPSILON);
    BOOST_CHECK_EQUAL(array.getSize(), 0);
    BOOST_CHECK_CLOSE(array.getCenter().x, 0.0, EPSILON);
    BOOST_CHECK_CLOSE(array.getCenter().x, 0.0, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().height, -1.0, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().width, -1.0, EPSILON);
    BOOST_CHECK_NO_THROW(array.move(DX, DY));
    BOOST_CHECK_NO_THROW(array.move(POINT));
    BOOST_CHECK_NO_THROW(array.printData());
    BOOST_CHECK_NO_THROW(array.scale(COEFFICIENT));
  }

  BOOST_AUTO_TEST_CASE(compositeShape_move_composite)
  {
    std::shared_ptr<unzhakov::Rectangle> rect = std::make_shared<unzhakov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    std::shared_ptr<unzhakov::Circle> circle = std::make_shared<unzhakov::Circle>(RADIUS, CENTRE);
    unzhakov::CompositeShape array;
    array.add(circle);
    array.add(rect);
    const unzhakov::rectangle_t frame = array.getFrameRect();
    const double area = array.getArea();
    const unzhakov::point_t centre = array.getCenter();
    unzhakov::CompositeShape array1;
    array1 = std::move(array);
    array.move(POINT);
    BOOST_CHECK_EQUAL(array1[0], circle);
    BOOST_CHECK_EQUAL(array1[1], rect);
    BOOST_CHECK_CLOSE(array1.getFrameRect().pos.x, centre.x, EPSILON);
    BOOST_CHECK_CLOSE(array1.getFrameRect().pos.y, centre.y, EPSILON);
    BOOST_CHECK_CLOSE(array1.getFrameRect().width, frame.width, EPSILON);
    BOOST_CHECK_CLOSE(array1.getFrameRect().height, frame.height, EPSILON);
    BOOST_CHECK_EQUAL(array1.getSize(), 2);
    BOOST_CHECK_CLOSE(array1.getArea(), area, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()
