#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>
#include <cmath>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include "polygon.hpp"

namespace maksimova
{
  class TestRunner
  {
  public:
    template<class TestFunc>
    void RunTest(TestFunc func, const std::string &test_name);

    template<class TestFunc, class expected_exc>
    void RunTest(TestFunc func, const expected_exc &exc, const std::string &test_name);

    void CheckFails();

  private:
    int fail_count = 0;
  };

  template<class T, class U>
  void AssertEqual(const T &left, const U &right, const std::string &line)
  {
    if (left != right)
    {
      std::string os;
      os = "Assertion failed: " + std::to_string(left) + " != " + std::to_string(right)
        + " line: " + line;
      throw std::logic_error(os);
    }
  }

  template<class T, class U>
  void AssertAccuracy(const T &left, const U &right, const std::string &line, const double accuracy = 0.00001)
  {
    if (left + accuracy < right || left - accuracy > right)
    {
      std::string os;
      os = "Assertion failed: " + std::to_string(left) + " != " + std::to_string(right)
        + " line: " + line;
      throw std::logic_error(os);
    }
  }

  void Assert(bool b, const std::string &line)
  {
    AssertEqual(b, true, line);
  }

  template<class TestFunc>
  void TestRunner::RunTest(TestFunc func, const std::string &test_name)
  {
    try
    {
      func();
    }
    catch (std::exception &e)
    {
      ++fail_count;
      std::cerr << test_name << " fail: " << e.what() << std::endl;
    }
  }

  template<class TestFunc, class expected_exc>
  void TestRunner::RunTest(TestFunc func, const expected_exc &ex, const std::string &test_name)
  {
    try
    {
      func();
      ++fail_count;
      std::cerr << test_name << " fail: exception not found" << std::endl;
    }
    catch (const expected_exc&)
    {
      return;
    }
    catch (...)
    {
      ++fail_count;
      std::cerr << test_name << " fail: unknown error" << std::endl;
    }
  }

  void TestRunner::CheckFails()
  {
    if (fail_count > 0)
    {
      std::cerr << fail_count << " unit tests failed." << std::endl;
      exit(1);
    }
  }

  void test_rotate_rectangle()
  {
    Rectangle rec(3.5, 2.6, {1, 1});
    const double d_angle = 45;
    const double angle_first = rec.getAngle();
    rec.rotate(d_angle);
    const double angle_second = rec.getAngle();
    Assert(angle_first + d_angle == angle_second, std::to_string(__LINE__));
    Assert(rec.get_width() == 3.5, std::to_string(__LINE__));
    Assert(rec.get_height() == 2.6, std::to_string(__LINE__));
    Assert(rec.getFrameRect().pos.x == 1, std::to_string(__LINE__));
    Assert(rec.getFrameRect().pos.y == 1, std::to_string(__LINE__));
  }

  void test_rotate_circle()
  {
    Circle circ1(5, {1,1});
    circ1.rotate(90);
    Assert(circ1.getRadius() == 5, std::to_string(__LINE__));
    Assert(circ1.getCenter().x == 1, std::to_string(__LINE__));
    Assert(circ1.getCenter().y == 1, std::to_string(__LINE__));
  }

  void test_rotate_comp_shape()
  {
    CompositeShape compShape;
    std::shared_ptr<Shape> rectangle1
        = std::make_shared<Rectangle>(Rectangle(6, 4, { 0, 0 }));
    std::shared_ptr<Shape> rectangle2
        = std::make_shared<Rectangle>(Rectangle(4, 6, { 0, 0 }));
    compShape.addShape(rectangle1);
    compShape.addShape(rectangle2);
    const double area = compShape.getArea();
    point_t pos = compShape.getFrameRect().pos;
    const double width = compShape.getFrameRect().width;
    const double height = compShape.getFrameRect().height;
    compShape.rotate(90);
    AssertAccuracy(area, compShape.getArea(),std::to_string(__LINE__));
    AssertAccuracy(pos.x, compShape.getFrameRect().pos.x, std::to_string(__LINE__));
    AssertAccuracy(pos.y, compShape.getFrameRect().pos.y, std::to_string(__LINE__));
    AssertAccuracy(width, compShape.getFrameRect().height, std::to_string(__LINE__));
    AssertAccuracy(height, compShape.getFrameRect().width, std::to_string(__LINE__));
  }

  void test_add_element_matrix()
  {
    Matrix matrix;
    std::shared_ptr<Shape> rec1 = std::make_shared<Rectangle>(Rectangle(4, 3, {1, 1}));
    std::shared_ptr<Shape> rec2 = std::make_shared<Rectangle>(Rectangle(4, 3, {3, 3}));
    std::shared_ptr<Shape> circ1 = std::make_shared<Circle>(Circle(3, {1, 1}));
    std::shared_ptr<Shape> circ2 = std::make_shared<Circle>(Circle(3, {10, 10}));
    std::shared_ptr<Shape> circ3 = std::make_shared<Circle>(Circle(3, {-10, -10}));
    matrix.addElement(rec1);
    matrix.addElement(rec2);
    matrix.addElement(circ1);
    matrix.addElement(circ2);
    matrix.addElement(circ3);
    Assert(matrix.getLevels() == 3, std::to_string(__LINE__));
    Assert(matrix.getColumns() == 3, std::to_string(__LINE__));
    Assert(matrix[0][0] == rec1, std::to_string(__LINE__));
    Assert(matrix[0][1] == circ2, std::to_string(__LINE__));
    Assert(matrix[0][2] == circ3, std::to_string(__LINE__));
    Assert(matrix[1][0] == rec2, std::to_string(__LINE__));
    Assert(matrix[2][0] == circ1, std::to_string(__LINE__));
  }

  void test_polygon_invalid_argument_1()
  {
    point_t point1{1,2};
    point_t *point = &point1;
    Polygon polygon(point, 1);
  }

  void test_polygon_invalid_argument_2()
  {
    point_t point{ 1, 2 };
    point_t point1{ 1, 4 };
    point_t point2{ 2, 3};
    point_t point3{ 4, 2 };
    point_t points[] = { point, point1, point2, point3 };
    Polygon polygon(points, 4);
  }

  void test_polygon_invalid_scale()
  {
    point_t point{ 1, 2 };
    point_t point1{ 1, 4 };
    point_t point2{ 2, 4};
    point_t point3{ 4, 2 };
    point_t points[] = { point, point1, point2, point3 };
    Polygon polygon(points, 4);
    polygon.scale(-1);
  }

  void test_polygon_scale()
  {
    point_t point{ 1, 2 };
    point_t point1{ 1, -1 };
    point_t point2{ -1, 1};
    point_t point3{ -1, -2 };
    point_t points[] = { point, point1, point2, point3 };
    Polygon polygon(points, 4);
    polygon.scale(2);
    point_t _s_point{ -2, 2 };
    point_t _s_point1{ -2, -4 };
    point_t _s_point2{ 2, -2};
    point_t _s_point3{ 2, 4 };
    AssertAccuracy(polygon[0].x, _s_point.x, std::to_string(__LINE__));
    AssertAccuracy(polygon[0].y, _s_point.y, std::to_string(__LINE__));
    AssertAccuracy(polygon[1].x, _s_point1.x, std::to_string(__LINE__));
    AssertAccuracy(polygon[1].y, _s_point1.y, std::to_string(__LINE__));
    AssertAccuracy(polygon[2].x, _s_point2.x, std::to_string(__LINE__));
    AssertAccuracy(polygon[2].y, _s_point2.y, std::to_string(__LINE__));
    AssertAccuracy(polygon[3].x, _s_point3.x, std::to_string(__LINE__));
    AssertAccuracy(polygon[3].y, _s_point3.y, std::to_string(__LINE__));
  }

  void test_rotate_polygon()
  {
    point_t point{ 3, 1 };
    point_t point1{ 3, -1 };
    point_t point2{ -3, 1};
    point_t point3{-3, -1};
    point_t points[] = {point, point1, point2, point3};
    Polygon polygon(points, 4);
    polygon.rotate(90);
    point_t _r_point{ -1, -3 };
    point_t _r_point1{ 1, -3 };
    point_t _r_point2{ 1,  3 };
    point_t _r_point3{ -1, 3 };
    AssertAccuracy(polygon[0].x, _r_point.x, std::to_string(__LINE__));
    AssertAccuracy(polygon[0].y, _r_point.y, std::to_string(__LINE__));
    AssertAccuracy(polygon[1].x, _r_point1.x, std::to_string(__LINE__));
    AssertAccuracy(polygon[1].y, _r_point1.y, std::to_string(__LINE__));
    AssertAccuracy(polygon[2].x, _r_point2.x, std::to_string(__LINE__));
    AssertAccuracy(polygon[2].y, _r_point2.y, std::to_string(__LINE__));
    AssertAccuracy(polygon[3].x, _r_point3.x, std::to_string(__LINE__));
    AssertAccuracy(polygon[3].y, _r_point3.y, std::to_string(__LINE__));
  }

  void all_test()
  {
    TestRunner tr;
    tr.RunTest(test_rotate_rectangle, "Test of the rectangle when you rotate");
    tr.RunTest(test_rotate_circle, "Test of the circle when you rotate");
    tr.RunTest(test_rotate_comp_shape, "Test of the composite shape when you rotate");
    tr.RunTest(test_add_element_matrix, "Test add element in matrix");
    tr.RunTest(test_polygon_invalid_argument_1, std::invalid_argument(""), "Test polygon invalid argument 1");
    tr.RunTest(test_polygon_invalid_argument_2, std::invalid_argument(""), "Test polygon invalid argument 1");
    tr.RunTest(test_polygon_invalid_scale, std::invalid_argument(""), "Test of the polygon when you scale");
    tr.RunTest(test_polygon_scale, "Test of the polygon when you scale");
    tr.RunTest(test_rotate_polygon, "Test of the polygon when you rotate");
    tr.CheckFails();
  }
}

int main()
{
  try
  {
    maksimova::all_test();
  }
  catch(...)
  {
    std::cerr << "Error.";
    return -1;
  }
  return 0;
}
