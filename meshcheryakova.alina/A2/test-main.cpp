#define BOOST_TEST_MODULE mytest

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "rectangle.hpp"
#include "circle.hpp"

const double ACCURACY = 0.0001;

BOOST_AUTO_TEST_CASE(test_invalid_radius_circle)
{
  BOOST_CHECK_THROW(meshcheryakova::Circle circle( {3.4, 2.0}, -3.1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_width_rectangle)
{
  BOOST_CHECK_THROW(meshcheryakova::Rectangle rectangle(-6.5, 1.8, {-2.1, 6.6}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_height_rectangle)
{
  BOOST_CHECK_THROW(meshcheryakova::Rectangle rectangle(6.5, -1.8, {-2.1, 6.6}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_coefficient_scaling_circle)
{
  meshcheryakova::Circle circle({3.3, 2.5}, 3.0);
  BOOST_CHECK_THROW(circle.scale(-5.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_coefficient_scaling_rectangle)
{
  meshcheryakova::Rectangle rectangle(6.3, 3.6, {-2.2, -5.0});
  BOOST_CHECK_THROW(rectangle.scale(-2.4), std::invalid_argument);
}

 BOOST_AUTO_TEST_CASE(test_permanence_rectangle_move)
{
  meshcheryakova::point_t spot{-1.0, 1.0};
  meshcheryakova::Rectangle rectangle{6.0, 5.0, spot};
  meshcheryakova::rectangle_t frame_rec = rectangle.getFrameRect();
  double area = rectangle.getArea();
  rectangle.move(spot);
  BOOST_CHECK_CLOSE(frame_rec.width, rectangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(frame_rec.height, rectangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(area, rectangle.getArea(), ACCURACY);
  rectangle.move(-9.0, 4.0);
  BOOST_CHECK_CLOSE(frame_rec.width, rectangle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(frame_rec.height, rectangle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(area, rectangle.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_permanence_circle_move)
{
  meshcheryakova::point_t spot{-1.0, 1.0};
  meshcheryakova::Circle circle{spot, 3.0};
  meshcheryakova::rectangle_t frame_rec = circle.getFrameRect();
  double area = circle.getArea();
  circle.move(spot);
  BOOST_CHECK_CLOSE(frame_rec.width, circle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(frame_rec.height, circle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(area, circle.getArea(), ACCURACY);
  circle.move(-9.0, 4.0);
  BOOST_CHECK_CLOSE(frame_rec.width, circle.getFrameRect().width, ACCURACY);
  BOOST_CHECK_CLOSE(frame_rec.height, circle.getFrameRect().height, ACCURACY);
  BOOST_CHECK_CLOSE(area, circle.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_correct_area_rectangle_scale)
{
  meshcheryakova::Rectangle rectangle(3.0, 4.0, {5.0, -5.0});
  double area = rectangle.getArea();
  double coefficient = 1.8;
  rectangle.scale(coefficient);
  BOOST_CHECK_CLOSE(area * coefficient * coefficient, rectangle.getArea(), ACCURACY);
}

BOOST_AUTO_TEST_CASE(test_correct_area_circle_scale)
{
  meshcheryakova::Circle circle({5.0, -5.0}, 3.2);
  double area = circle.getArea();
  double coefficient = 1.8;
  circle.scale(coefficient);
  BOOST_CHECK_CLOSE(area * coefficient * coefficient, circle.getArea(), ACCURACY);
}

