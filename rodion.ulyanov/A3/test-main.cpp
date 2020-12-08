#include <cmath>
#include <stdexcept>
#include <cassert>
#include <vector>
#include <functional>
#include "base-types.hpp"
#include "triangle.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

const double ACCURACY = 0.0001;

bool checkClose(double pre_value, double post_value, double accuracy);

typedef void (*initShape)();

template <typename T>
bool checkException(initShape func)
{
 try
 {
   func();
 }
 catch (T &e)
 {
   return true;
 }
 return false;
}

void compositeShapeMoveTest() {
 rodion::Circle circle(50.0, {10.0, 10.0});
 rodion::Rectangle rectangle({10.0, 5.0, {20.0, 25.0}});
 rodion::Triangle triangle({10.0, 12.0}, {24.0, 11.0}, {5.0, 21.0});
 rodion::CompositeShape composite_shape(3);
 composite_shape.addShape(std::make_shared<rodion::Rectangle>(rectangle));
 composite_shape.addShape(std::make_shared<rodion::Circle>(circle));
 composite_shape.addShape(std::make_shared<rodion::Triangle>(triangle));
 rodion::rectangle_t pre_frame = composite_shape.getFrameRect();
 composite_shape.move(10, 10);
 assert(checkClose(composite_shape.getFrameRect().pos.x, pre_frame.pos.x + 10 , ACCURACY));
 assert(checkClose(composite_shape.getFrameRect().pos.y, pre_frame.pos.y + 10, ACCURACY));
 composite_shape.move({10, 10});
 assert(checkClose(composite_shape.getFrameRect().pos.x, 10, ACCURACY));
 assert(checkClose(composite_shape.getFrameRect().pos.y, 10, ACCURACY));
 assert(checkClose(composite_shape.getFrameRect().width, pre_frame.width, ACCURACY));
 assert(checkClose(composite_shape.getFrameRect().height, pre_frame.height, ACCURACY));
}
void compositeShapeScaleTest() {
 rodion::Circle circle(50.0, {10.0, 10.0});
 rodion::Rectangle rectangle({10.0, 5.0, {20.0, 25.0}});
 rodion::Triangle triangle({10.0, 10.0}, {24.0, 11.0}, {-5.0, 21.0});
 rodion::CompositeShape composite_shape(3);
 composite_shape.addShape(std::make_shared<rodion::Circle>(circle));
 composite_shape.addShape(std::make_shared<rodion::Rectangle>(rectangle));
 composite_shape.addShape(std::make_shared<rodion::Triangle>(triangle));
 const double pre_area = composite_shape.getArea();
 const double scale_value = 2;
 composite_shape.scale(scale_value);
 assert(checkClose(pre_area * scale_value * scale_value, composite_shape.getArea(), ACCURACY));
}

void compositeShapeAddShapeTest()
{
 rodion::Rectangle rectangle({10.0, 5.0, {20.0, 25.0}});
 rodion::CompositeShape composite_shape(3);
 std::shared_ptr<rodion::Shape> shape = std::make_shared<rodion::Rectangle>(rectangle);
 composite_shape.addShape(shape);
 assert(composite_shape.getSize() == 1);
 assert(composite_shape[0] == shape);
}

void compositeShapeRemoveShapeTest()
{
 rodion::Rectangle rectangle({10.0, 5.0, {20.0, 25.0}});
 rodion::CompositeShape composite_shape(3);
 composite_shape.addShape(std::make_shared<rodion::Rectangle>(rectangle));
 composite_shape.removeShape(0);
 assert(composite_shape.getSize() == 0);
}

void compositeShapeGetAreaTest()
{
 rodion::Circle circle(50.0, {10.0, 10.0});
 rodion::Rectangle rectangle({10.0, 5.0, {20.0, 25.0}});
 rodion::Triangle triangle({10.0, 10.0}, {24.0, 11.0}, {-5.0, 21.0});
 rodion::CompositeShape composite_shape(3);
 std::shared_ptr<rodion::Shape> shape_one = std::make_shared<rodion::Circle>(circle);
 composite_shape.addShape(shape_one);
 std::shared_ptr<rodion::Shape> shape_two = std::make_shared<rodion::Rectangle>(rectangle);
 composite_shape.addShape(shape_two);
 std::shared_ptr<rodion::Shape> shape_three = std::make_shared<rodion::Triangle>(triangle);
 composite_shape.addShape(shape_three);
 assert(checkClose(composite_shape.getArea(), shape_one->getArea() + shape_two->getArea() + shape_three->getArea(), ACCURACY));
}

void compositeShapeGetFrameRectTest()
{
 rodion::Circle circle(6.0, {5.0, 5.0});
 rodion::Rectangle rectangle({8.0, 6.0, {10.0, 10.0}});
 rodion::Triangle triangle({10.0, 10.0}, {5.0, 10.0}, {-5.0, 7.0});
 rodion::CompositeShape compositeShape(3);
 std::shared_ptr<rodion::Shape> shape_one = std::make_shared<rodion::Rectangle>(rectangle);
 compositeShape.addShape(shape_one);
 std::shared_ptr<rodion::Shape> shape_two = std::make_shared<rodion::Circle>(circle);
 compositeShape.addShape(shape_two);
 std::shared_ptr<rodion::Shape> shape_three = std::make_shared<rodion::Triangle>(triangle);
 compositeShape.addShape(shape_three);
 rodion::rectangle_t rectangle_frame = shape_one->getFrameRect();
 rodion::rectangle_t circle_frame = shape_two->getFrameRect();
 rodion::rectangle_t triangle_frame = shape_three->getFrameRect();
 assert(checkClose(compositeShape.getFrameRect().height,
     (rectangle_frame.pos.y + rectangle_frame.height / 2) - (circle_frame.pos.y - circle_frame.height / 2), ACCURACY));
 assert(checkClose(compositeShape.getFrameRect().width,
     (rectangle_frame.pos.x + rectangle_frame.width / 2) - (triangle_frame.pos.x - triangle_frame.width / 2), ACCURACY));
 assert(checkClose(compositeShape.getFrameRect().pos.x,
     (triangle_frame.pos.x - triangle_frame.width / 2) + (compositeShape.getFrameRect().width / 2), ACCURACY));
 assert(checkClose(compositeShape.getFrameRect().pos.y,
     (circle_frame.pos.y - circle_frame.height / 2) + (compositeShape.getFrameRect().height / 2), ACCURACY));
}

void compositeShapeInvalidCapacityTest()
{
 assert(checkException<std::invalid_argument>([]()
 {
   rodion::CompositeShape composite_shape(0);
 }));
}

void compositeShapeInvalidIndexTest()
{
 assert(checkException<std::out_of_range>([]()
 {
   rodion::CompositeShape composite_shape(1);
   composite_shape[0];
 }));

 assert(checkException<std::out_of_range>([]()
 {
   rodion::CompositeShape composite_shape(1);
   composite_shape.removeShape(0);
 }));
}

void compositeShapeInvalidShapeToAddTest()
{
 assert(checkException<std::invalid_argument>([]()
 {
   rodion::CompositeShape composite_shape(1);
   composite_shape.addShape(nullptr);
 }));
}

void compositeShapeInvalidScaleValueTest()
{
 assert(checkException<std::invalid_argument>([]()
 {
   rodion::CompositeShape composite_shape(1);
   composite_shape.scale(-1);
 }));
}

int main()
{
 std::vector<std::function<void()>> tests =
 {
     compositeShapeAddShapeTest, compositeShapeRemoveShapeTest, compositeShapeGetAreaTest,
     compositeShapeGetFrameRectTest, compositeShapeMoveTest, compositeShapeScaleTest,
     compositeShapeInvalidCapacityTest, compositeShapeInvalidIndexTest, compositeShapeInvalidShapeToAddTest,
     compositeShapeInvalidScaleValueTest
 };
 for (auto &test : tests)
 {
   test();
 }
 return 0;
}

bool checkClose(double pre_value, double post_value, double accuracy)
{
 return std::abs(pre_value - post_value) < accuracy;
}

