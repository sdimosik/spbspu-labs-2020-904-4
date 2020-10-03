#define BOOST_TEST_MODULE mytest

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

BOOST_AUTO_TEST_CASE(test_invalid_argument_rectangle)
{
  BOOST_CHECK_THROW(sviridov::Rectangle rectangle({2, 2},-1, 3), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_circle)
{
  BOOST_CHECK_THROW(sviridov::Circle circle({2, 2}, -10), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_triangle)
{
  BOOST_CHECK_THROW(sviridov::Triangle triangle({0, 0}, {5, 5}, {10, 10}), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_move_point_rectangle)
{
  sviridov::Rectangle rectangle({1,1}, 10, 14.5);
  const sviridov::rectangle_t frame_rectangle = rectangle.getFrameRect();
  rectangle.move({100, -100});
  BOOST_CHECK_CLOSE(frame_rectangle.height, rectangle.getFrameRect().height, 0.001);
  BOOST_CHECK_CLOSE(frame_rectangle.width, rectangle.getFrameRect().width, 0.001);
}

BOOST_AUTO_TEST_CASE(test_move_point_circle)
{
  sviridov::Circle circle({0,0}, 7);
  const sviridov::rectangle_t frame_circle = circle.getFrameRect();
  circle.move({100, -100});
  BOOST_CHECK_CLOSE(frame_circle.width, circle.getFrameRect().width, 0.001);
}

BOOST_AUTO_TEST_CASE(test_move_point_triangle)
{
  sviridov::Triangle triangle({1, 1}, {2, 10}, {0, 0});
  const sviridov::point_t tri_vertex[3] = {triangle.getPosVertexA(), triangle.getPosVertexB(), triangle.getPosVertexC()};
  triangle.move({100, -100});
  BOOST_CHECK_CLOSE(sqrt((tri_vertex[0].x - tri_vertex[1].x) * (tri_vertex[0].x - tri_vertex[1].x)
      + (tri_vertex[0].y - tri_vertex[1].y) * (tri_vertex[0].y - tri_vertex[1].y)),
      sqrt((triangle.getPosVertexA().x - triangle.getPosVertexB().x) *
      (triangle.getPosVertexA().x - triangle.getPosVertexB().x)
      + (triangle.getPosVertexA().y - triangle.getPosVertexB().y) *
      (triangle.getPosVertexA().y - triangle.getPosVertexB().y)), 0.001);
  BOOST_CHECK_CLOSE(sqrt((tri_vertex[1].x - tri_vertex[2].x) * (tri_vertex[1].x - tri_vertex[2].x)
      + (tri_vertex[1].y - tri_vertex[2].y) * (tri_vertex[1].y - tri_vertex[2].y)),
      sqrt((triangle.getPosVertexB().x - triangle.getPosVertexC().x) *
      (triangle.getPosVertexB().x - triangle.getPosVertexC().x)
      + (triangle.getPosVertexB().y - triangle.getPosVertexC().y) *
      (triangle.getPosVertexB().y - triangle.getPosVertexC().y)), 0.001);
  BOOST_CHECK_CLOSE(sqrt((tri_vertex[2].x - tri_vertex[0].x) * (tri_vertex[2].x - tri_vertex[0].x)
      + (tri_vertex[2].y - tri_vertex[0].y) * (tri_vertex[2].y - tri_vertex[0].y)),
      sqrt((triangle.getPosVertexA().x - triangle.getPosVertexC().x) *
      (triangle.getPosVertexA().x - triangle.getPosVertexC().x)
      + (triangle.getPosVertexA().y - triangle.getPosVertexC().y) *
      (triangle.getPosVertexA().y - triangle.getPosVertexC().y)), 0.001);
}
BOOST_AUTO_TEST_CASE(test_move_point_rectangle_area)
{
  sviridov::Rectangle rectangle({1,1}, 10, 14.5);
  const double area_rectangle = rectangle.getArea();
  rectangle.move({1,1});
  BOOST_CHECK_CLOSE(area_rectangle, rectangle.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(test_move_point_circle_area)
{
  sviridov::Circle circle({0,0}, 7);
  const double area_circle = circle.getArea();
  circle.move({1,1});
  BOOST_CHECK_CLOSE(area_circle, circle.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(test_move_point_triangle_area)
{
  sviridov::Triangle triangle({1,1}, {2,10}, {0,0});
  const double area_triangle = triangle.getArea();
  triangle.move({1,1});
  BOOST_CHECK_CLOSE(area_triangle, triangle.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(test_move_delta_rectangle)
{
  sviridov::Rectangle rectangle({1,1}, 10, 14.5);
  const sviridov::rectangle_t frame_rectangle = rectangle.getFrameRect();
  rectangle.move(-11, 4);
  BOOST_CHECK_CLOSE(frame_rectangle.height, rectangle.getFrameRect().height, 0.001);
  BOOST_CHECK_CLOSE(frame_rectangle.width, rectangle.getFrameRect().width, 0.001);
}

BOOST_AUTO_TEST_CASE(test_move_delta_circle)
{
  sviridov::Circle circle({0,0}, 7);
  const sviridov::rectangle_t frame_circle = circle.getFrameRect();
  circle.move(10, -6);
  BOOST_CHECK_CLOSE(frame_circle.width, circle.getFrameRect().width, 0.001);
}

BOOST_AUTO_TEST_CASE(test_move_delta_triangle)
{
  sviridov::Triangle triangle({1, 1}, {2, 10}, {0, 0});
  const sviridov::point_t tri_vertex[3]= {triangle.getPosVertexA(), triangle.getPosVertexB(), triangle.getPosVertexC() };
  triangle.move(-1, 0);
  BOOST_CHECK_CLOSE(sqrt((tri_vertex[0].x - tri_vertex[1].x) * (tri_vertex[0].x - tri_vertex[1].x)
      + (tri_vertex[0].y - tri_vertex[1].y) * (tri_vertex[0].y - tri_vertex[1].y)),
      sqrt((triangle.getPosVertexA().x - triangle.getPosVertexB().x) * (triangle.getPosVertexA().x - triangle.getPosVertexB().x)
      + (triangle.getPosVertexA().y - triangle.getPosVertexB().y) * (triangle.getPosVertexA().y - triangle.getPosVertexB().y)), 0.001);
  BOOST_CHECK_CLOSE(sqrt((tri_vertex[1].x - tri_vertex[2].x) * (tri_vertex[1].x - tri_vertex[2].x)
      + (tri_vertex[1].y - tri_vertex[2].y) * (tri_vertex[1].y - tri_vertex[2].y)),
      sqrt((triangle.getPosVertexB().x - triangle.getPosVertexC().x) * (triangle.getPosVertexB().x - triangle.getPosVertexC().x)
      + (triangle.getPosVertexB().y - triangle.getPosVertexC().y) * (triangle.getPosVertexB().y - triangle.getPosVertexC().y)), 0.001);
  BOOST_CHECK_CLOSE(sqrt((tri_vertex[2].x - tri_vertex[0].x) * (tri_vertex[2].x - tri_vertex[0].x)
      + (tri_vertex[2].y - tri_vertex[0].y) * (tri_vertex[2].y - tri_vertex[0].y)),
      sqrt((triangle.getPosVertexA().x - triangle.getPosVertexC().x) * (triangle.getPosVertexA().x - triangle.getPosVertexC().x)
      + (triangle.getPosVertexA().y - triangle.getPosVertexC().y) * (triangle.getPosVertexA().y - triangle.getPosVertexC().y)), 0.001);
}

BOOST_AUTO_TEST_CASE(test_move_delta_rectangle_area)
{
  sviridov::Rectangle rectangle({1,1}, 10, 14.5);
  const double area_rectangle = rectangle.getArea();
  rectangle.move(1,1);
  BOOST_CHECK_CLOSE(area_rectangle, rectangle.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(test_move_delta_circle_area)
{
  sviridov::Circle circle({0,0}, 7);
  const double area_circle = circle.getArea();
  circle.move(1,1);
  BOOST_CHECK_CLOSE(area_circle, circle.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(test_move_delta_triangle_area)
{
  sviridov::Triangle triangle({1,1}, {2,10}, {0,0});
  const double area_triangle = triangle.getArea();
  triangle.move(1,1);
  BOOST_CHECK_CLOSE(area_triangle, triangle.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(test_scale_rectangle_area)
{
  sviridov::Rectangle rectangle({1,1}, 10, 14.5);
  const double area_rectangle = rectangle.getArea(), scale = 2;
  rectangle.scale(scale);
  BOOST_CHECK_CLOSE(area_rectangle * scale * scale, rectangle.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(test_scale_circle_area)
{
  sviridov::Circle circle({0,0}, 7);
  const double area_circle = circle.getArea(), scale = 0.3;
  circle.scale(scale);
  BOOST_CHECK_CLOSE(area_circle * scale * scale, circle.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(test_scale_triangle_area)
{
  sviridov::Triangle triangle({1,1}, {2,10}, {0,0});
  const double area_triangle = triangle.getArea(), scale = 10;
  triangle.scale(scale);
  BOOST_CHECK_CLOSE(area_triangle * scale * scale, triangle.getArea(), 0.001);
}
