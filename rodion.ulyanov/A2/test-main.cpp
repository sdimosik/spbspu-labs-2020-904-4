#include <cmath>
#include <cassert>
#include <vector>
#include <functional>
#include "triangle.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

bool isEqualAround (double pre_value, double post_value) {
 const double ACCURACY = 0.00001;
 return std::abs(pre_value - post_value) < ACCURACY;
}

typedef void (*initShape)();

bool checkException(initShape func)
{
 try
 {
   func();
 }
 catch (std::invalid_argument &e)
 {
   return true;
 }
 return false;
}


void circleMoveTest() {
 rodion::Circle post_circle(50.0, {10.0, 10.0});
 rodion::rectangle_t pre_circle_frame = post_circle.getFrameRect();
 const double pre_area = post_circle.getArea();
 post_circle.move(14.2, 23.0);
 assert(isEqualAround(pre_circle_frame.height, post_circle.getFrameRect().height));
 assert(isEqualAround(pre_circle_frame.width, post_circle.getFrameRect().width));
 assert(isEqualAround(pre_area, post_circle.getArea()));
 post_circle.move({32.34, 45.76});
 assert(isEqualAround(pre_circle_frame.height, post_circle.getFrameRect().height));
 assert(isEqualAround(pre_circle_frame.width, post_circle.getFrameRect().width));
 assert(isEqualAround(pre_area, post_circle.getArea()));
}

void rectangleMoveTest() {
 rodion::Rectangle post_rectangle({20.0, 50.0, {10.0, 10.0}});
 rodion::rectangle_t pre_rectangle_frame = post_rectangle.getFrameRect();
 const double pre_area = post_rectangle.getArea();
 post_rectangle.move(14.2, 23.0);
 assert(isEqualAround(pre_rectangle_frame.height, post_rectangle.getFrameRect().height));
 assert(isEqualAround(pre_rectangle_frame.width, post_rectangle.getFrameRect().width));
 assert(isEqualAround(pre_area, post_rectangle.getArea()));
 post_rectangle.move({32.34, 45.76});
 assert(isEqualAround(pre_rectangle_frame.height, post_rectangle.getFrameRect().height));
 assert(isEqualAround(pre_rectangle_frame.width, post_rectangle.getFrameRect().width));
 assert(isEqualAround(pre_area, post_rectangle.getArea()));
}

void triangleMoveTest() {
 rodion::Triangle post_triangle({10.0, 10.0}, {24.0, 11.0}, {-5.0, 21.0});
 rodion::rectangle_t pre_triangle_frame = post_triangle.getFrameRect();
 const double pre_area = post_triangle.getArea();
 post_triangle.move(14.2, 23.0);
 assert(isEqualAround(pre_triangle_frame.height, post_triangle.getFrameRect().height));
 assert(isEqualAround(pre_triangle_frame.width, post_triangle.getFrameRect().width));
 assert(isEqualAround(pre_area, post_triangle.getArea()));
 post_triangle.move({32.34, 45.76});
 assert(isEqualAround(pre_triangle_frame.height, post_triangle.getFrameRect().height));
 assert(isEqualAround(pre_triangle_frame.width, post_triangle.getFrameRect().width));
 assert(isEqualAround(pre_area, post_triangle.getArea()));
}

void circleScaleTest() {
 rodion::Circle circle(5.0, {10.0, 10.0});
 const double pre_area = circle.getArea();
 circle.scale(3.0);
 assert(isEqualAround(circle.getArea(), pre_area * pow(3, 2)));
}

void rectangleScaleTest() {
 rodion::Rectangle rectangle ({10.0, 5.0, {20.0, 25.0}});
 const double pre_area = rectangle.getArea();
 rectangle.scale(3.0);
 assert(isEqualAround(rectangle.getArea(), pre_area * pow(3, 2)));
}

void triangleScaleTest() {
 rodion::Triangle triangle ({10.0, 10.0}, {24.0, 11.0}, {5.0, 21.0});
 const double pre_area = triangle.getArea();
 triangle.scale(3.0);
 assert(isEqualAround(triangle.getArea(), pre_area * pow(3, 2)));
}

void circleInvalidArgumentTest() {
 assert(checkException([]() {
   rodion::Circle(-1, {10, 10});
 }));
}

void rectangleInvalidArgumentTest() {
 assert(checkException([]() {
   rodion::Rectangle({-1, 2, {10, 10}});
 }));
}

void triangleInvalidArgumentTest() {
 assert(checkException([]() {
   rodion::Triangle({10.0, 10.0}, {10.0, 10.0}, {-5.0, 21.0});
 }));
}

void circleInvalidScaleArgumentTest() {
 assert(checkException([]() {
   rodion::Circle circle(10.0, {10.0, 10.0});
   circle.scale(-2.0);
 }));
}

void rectangleInvalidScaleArgumentTest() {
 assert(checkException([]() {
   rodion::Rectangle rectangle({10.0, 10.0, {10.0, 10.0}});
   rectangle.scale(-2.0);
 }));
}

void triangleInvalidScaleArgumentTest() {
 assert(checkException([]() {
   rodion::Triangle triangle({10.0, 10.0}, {11.0, 10.0}, {-5.0, 21.0});
   triangle.scale(-2.0);
 }));
}

int main() {
 std::vector<std::function<void()>> tests = {
   circleMoveTest, rectangleMoveTest, triangleMoveTest,
   circleInvalidArgumentTest, rectangleInvalidArgumentTest, triangleInvalidArgumentTest,
   circleInvalidScaleArgumentTest, rectangleInvalidScaleArgumentTest, triangleInvalidScaleArgumentTest,
   circleScaleTest, rectangleScaleTest, triangleScaleTest
 };
 for(auto & test : tests)
 {
   test();
 }
 return 0;
}
