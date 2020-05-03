#define BOOST_TEST_MODULE testA2

#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "circle.hpp"
#include "rectangle.hpp"

const double accuracy = 0.00001;

BOOST_AUTO_TEST_CASE(no_changing_parameters_after_moving_circle)
{
  spasoevich::Circle testCircle({ 3.0, 4.6 }, 5.5);
  const spasoevich::rectangle_t InitialFrameRect = testCircle.getFrameRect();
  const double InitialArea = testCircle.getArea();

  testCircle.move({ 7, 8 });
  BOOST_CHECK_CLOSE(InitialFrameRect.width, testCircle.getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(InitialFrameRect.height, testCircle.getFrameRect().height, accuracy);
  BOOST_CHECK_CLOSE(InitialArea, testCircle.getArea(), accuracy);

  testCircle.move(-5, -6);
  BOOST_CHECK_CLOSE(InitialFrameRect.width, testCircle.getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(InitialFrameRect.height, testCircle.getFrameRect().height, accuracy);
  BOOST_CHECK_CLOSE(InitialArea, testCircle.getArea(), accuracy);
}

BOOST_AUTO_TEST_CASE(no_changing_parameters_after_moving_rectangle)
{
  spasoevich::Rectangle testRectangle({ 3.2, 4.0 }, 5.3, 6.4);
  const spasoevich::rectangle_t InitialFrameRect = testRectangle.getFrameRect();
  const double InitialArea = testRectangle.getArea();

  testRectangle.move({ 7, 8 });
  BOOST_CHECK_CLOSE(InitialFrameRect.width, testRectangle.getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(InitialFrameRect.height, testRectangle.getFrameRect().height, accuracy);
  BOOST_CHECK_CLOSE(InitialArea, testRectangle.getArea(), accuracy);

  testRectangle.move(-5, -6);
  BOOST_CHECK_CLOSE(InitialFrameRect.width, testRectangle.getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(InitialFrameRect.height, testRectangle.getFrameRect().height, accuracy);
  BOOST_CHECK_CLOSE(InitialArea, testRectangle.getArea(), accuracy);
}

BOOST_AUTO_TEST_CASE(changing_circle_area_correctly_after_scaling)
{
  spasoevich::Circle testCircle({ 3.6, 4.6 }, 5.6);
  const double InitialArea = testCircle.getArea();
  const double coefficient = 4;

  testCircle.scale(coefficient);
  BOOST_CHECK_CLOSE(testCircle.getArea(), coefficient * coefficient * InitialArea, accuracy);
}

BOOST_AUTO_TEST_CASE(changing_rectangle_area_correctly_after_scaling)
{
  spasoevich::Rectangle testRectangle({ { 4.0, 5.3 }, 6.2, 7.0 });
  const double InitialArea = testRectangle.getArea();
  const double coefficient = 3;

  testRectangle.scale(coefficient);
  BOOST_CHECK_CLOSE(testRectangle.getArea(), coefficient * coefficient * InitialArea, accuracy);
}

BOOST_AUTO_TEST_CASE(invalid_radius_circle)
{
  BOOST_CHECK_THROW(spasoevich::Circle testCircle({ 0.4, 4.0 }, -3.5), std::invalid_argument);
  BOOST_CHECK_THROW(spasoevich::Circle testCircle({ 0.4, 4.0 }, 0.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_coefficient_scaling_circle)
{
  spasoevich::Circle testCircle({ 4.4, 6.6 }, 3.5);
  BOOST_CHECK_THROW(testCircle.scale(-3.2), std::invalid_argument);
  BOOST_CHECK_THROW(testCircle.scale(0.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_width_rectangle)
{
  BOOST_CHECK_THROW(spasoevich::Rectangle rectangle({ -2.3, 6.0 }, -3.4, 6.6), std::invalid_argument);
  BOOST_CHECK_THROW(spasoevich::Rectangle rectangle({ -2.3, 6.0 }, 0.0, 4.5), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_height_rectangle)
{
  BOOST_CHECK_THROW(spasoevich::Rectangle rectangle({ -2.3, 6.0 }, 3.3, -4.7), std::invalid_argument);
  BOOST_CHECK_THROW(spasoevich::Rectangle rectangle({ -2.3, 6.0 }, 3.3, 0.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_coefficient_scaling_rectangle)
{
  spasoevich::Rectangle testRectangle({ -2.3, 6.0 }, 3.4, 6.7);
  BOOST_CHECK_THROW(testRectangle.scale(-4.0), std::invalid_argument);
  BOOST_CHECK_THROW(testRectangle.scale(0.0), std::invalid_argument);
}
