#define BOOST_TEST_MODULE testA3

#include <stdexcept>
#include <memory>

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

const double accuracy = 0.00000001;

BOOST_AUTO_TEST_CASE(check_no_changing_parameters_after_moving_composite_shape)
{
  spasoevich::Circle circle({ 4.9, 4.5 }, 8.7);
  spasoevich::CompositeShape::shape_ptr testCircle = std::make_shared<spasoevich::Circle>(circle);
  spasoevich::Rectangle rectangle({ { 5, 6 }, 7.8, 8.9 });
  spasoevich::CompositeShape::shape_ptr testRectangle = std::make_shared<spasoevich::Rectangle>(rectangle);
  spasoevich::CompositeShape testComposite;
  testComposite.addShape(testCircle);
  testComposite.addShape(testRectangle);
  const spasoevich::rectangle_t frameRectBefore = testComposite.getFrameRect();
  const double areaBefore = testComposite.getArea();

  testComposite.move({ 1.9, 1.9 });
  BOOST_CHECK_CLOSE(frameRectBefore.width, testComposite.getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(frameRectBefore.height, testComposite.getFrameRect().height, accuracy);
  BOOST_CHECK_CLOSE(areaBefore, testComposite.getArea(), accuracy);

  testComposite.move(5, -7);
  BOOST_CHECK_CLOSE(frameRectBefore.width, testComposite.getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(frameRectBefore.height, testComposite.getFrameRect().height, accuracy);
  BOOST_CHECK_CLOSE(areaBefore, testComposite.getArea(), accuracy);
}

BOOST_AUTO_TEST_CASE(check_changing_area_correctly_after_scaling_composite_shape)
{
  spasoevich::Circle circle({ 4, 4 }, 3);
  spasoevich::CompositeShape::shape_ptr testCircle = std::make_shared<spasoevich::Circle>(circle);
  spasoevich::Rectangle rectangle({ { 5, 6 }, 2.1, 1 });
  spasoevich::CompositeShape::shape_ptr testRectangle = std::make_shared<spasoevich::Rectangle>(rectangle);
  spasoevich::CompositeShape testComposite;
  testComposite.addShape(testCircle);
  testComposite.addShape(testRectangle);
  double areaBefore = testComposite.getArea();

  double coefficient = 2.75;
  testComposite.scale(coefficient);
  BOOST_CHECK_CLOSE(testComposite.getArea(), coefficient * coefficient * areaBefore, accuracy);
  areaBefore = testComposite.getArea();

  coefficient = 0.75;
  testComposite.scale(coefficient);
  BOOST_CHECK_CLOSE(testComposite.getArea(), coefficient * coefficient * areaBefore, accuracy);
}

BOOST_AUTO_TEST_CASE(check_correct_using_of_operators_move_copy)
{
  spasoevich::Circle circle({ 1, 2 }, 3);
  spasoevich::CompositeShape::shape_ptr testCircle = std::make_shared<spasoevich::Circle>(circle);
  spasoevich::CompositeShape testComposite;
  testComposite.addShape(testCircle);

  BOOST_CHECK_NO_THROW(spasoevich::CompositeShape testComposite2(testComposite));
  BOOST_CHECK_NO_THROW(spasoevich::CompositeShape testComposite2(std::move(testComposite)));

  spasoevich::CompositeShape testComposite2;
  testComposite2.addShape(testCircle);

  spasoevich::CompositeShape testComposite3;

  BOOST_CHECK_NO_THROW(testComposite3 = testComposite2);
  BOOST_CHECK_NO_THROW(testComposite3 = std::move(testComposite2));
}

