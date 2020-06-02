#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

namespace maksimova
{
  template<class T, class U>
  void AssertEqual(const T &left, const U &right, const std::string &line);

  void Assert(bool b, const std::string &line);

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

  void test_incorrect_parameters_in_scale_csh()
  {
    CompositeShape shapes;
    shapes.scale(-5);
  }

  void test_invalid_index_csh()
  {
    CompositeShape shapes;
    shapes[0];
  }

  void test_invalid_argument_added_shape()
  {
    CompositeShape shapes;
    std::shared_ptr<Shape> shape = nullptr;
    shapes.addShape(shape);
  }

  void test_invalid_argument_deleted_shape()
  {
    CompositeShape shapes;
    shapes.deleteShape(0);
  }

  void test_move_composite_shape()
  {
    maksimova::Rectangle rec(2, 3, {1, 1});
    maksimova::Circle circ(3, {6, 6});
    CompositeShape shapes(2);
    std::shared_ptr<maksimova::Shape> shape1 = std::make_shared<maksimova::Rectangle>(rec);
    std::shared_ptr<maksimova::Shape> shape2 = std::make_shared<maksimova::Circle>(circ);
    shapes.addShape(shape1);
    shapes.addShape(shape2);
    double dx = 2.5, dy = 3.0;
    shapes.move(dx, dy);
    AssertEqual(rec.getFrameRect().pos.x + dx, shapes[0]->getFrameRect().pos.x,
        std::to_string(__LINE__) + ", in file " + __FILE__);
    AssertEqual(rec.getFrameRect().pos.y + dy, shapes[0]->getFrameRect().pos.y,
        std::to_string(__LINE__) + ", in file " + __FILE__);
    AssertEqual(circ.getFrameRect().pos.x + dx, shapes[1]->getFrameRect().pos.x,
        std::to_string(__LINE__) + ", in file " + __FILE__);
    AssertEqual(circ.getFrameRect().pos.y + dy, shapes[1]->getFrameRect().pos.y,
        std::to_string(__LINE__) + ", in file " + __FILE__);
  }

  void  test_area_in_move_composite_shape ()
  {
    maksimova::Rectangle rec(2, 3, {1, 1});
    maksimova::Circle circ(3, {6, 6});
    CompositeShape shapes(2);
    std::shared_ptr<maksimova::Shape> shape1 = std::make_shared<maksimova::Rectangle>(rec);
    std::shared_ptr<maksimova::Shape> shape2 = std::make_shared<maksimova::Circle>(circ);
    shapes.addShape(shape1);
    shapes.addShape(shape2);
    point_t pos {12, 12};
    double area = shapes.getArea();
    shapes.move(pos);
    AssertEqual(pos.x, shapes.getFrameRect().pos.x,
        std::to_string(__LINE__) + ", in file " + __FILE__);
    AssertEqual(pos.y, shapes.getFrameRect().pos.y,
        std::to_string(__LINE__) + ", in file " + __FILE__);
    AssertEqual(area, shapes.getArea(),
        std::to_string(__LINE__) + ", in file " + __FILE__);
  }

  void test_get_area_in_scale ()
  {
    maksimova::Rectangle rec(2, 3, {1, 1});
    maksimova::Circle circ(3, {6, 6});
    CompositeShape shapes(2);
    std::shared_ptr<maksimova::Shape> shape1 = std::make_shared<maksimova::Rectangle>(rec);
    std::shared_ptr<maksimova::Shape> shape2 = std::make_shared<maksimova::Circle>(circ);
    shapes.addShape(shape1);
    shapes.addShape(shape2);
    double area = shapes.getArea();
    double inaccuracy = 0.0000001;
    double  coefficient = 2;
    shapes.scale(coefficient);
    Assert(((area * coefficient * coefficient) < (shapes.getArea() + inaccuracy)
        && (area * coefficient * coefficient) > (shapes.getArea() - inaccuracy)),
        std::to_string(__LINE__) + ", in file " + __FILE__);
  }

  void test_area_at_addition ()
  {
    maksimova::Rectangle rec(2, 3, {1, 1});
    maksimova::Circle circ(3, {6, 6});
    CompositeShape shapes(2);
    std::shared_ptr<maksimova::Shape> shape1 = std::make_shared<maksimova::Rectangle>(rec);
    std::shared_ptr<maksimova::Shape> shape2 = std::make_shared<maksimova::Circle>(circ);
    shapes.addShape(shape1);
    shapes.addShape(shape2);
    AssertEqual(shapes.getArea(), rec.getArea() + circ.getArea(),
        std::to_string(__LINE__) + ", in file " + __FILE__);
  }

  void test_get_frame_rect()
  {
    maksimova::Rectangle rec(2, 3, {1, 1});
    maksimova::Circle circ(3, {6, 6});
    CompositeShape shapes(2);
    std::shared_ptr<maksimova::Shape> shape1 = std::make_shared<maksimova::Rectangle>(rec);
    std::shared_ptr<maksimova::Shape> shape2 = std::make_shared<maksimova::Circle>(circ);
    shapes.addShape(shape1);
    shapes.addShape(shape2);
    AssertEqual(shapes.getFrameRect().pos.x, 4.5,
        std::to_string(__LINE__) + ", in file " + __FILE__);
    AssertEqual(shapes.getFrameRect().pos.y, 4.25,
        std::to_string(__LINE__) + ", in file " + __FILE__);
    AssertEqual(shapes.getFrameRect().width, 9,
        std::to_string(__LINE__) + ", in file " + __FILE__);
    AssertEqual(shapes.getFrameRect().height, 9.5,
        std::to_string(__LINE__) + ", in file " + __FILE__);
  }

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

  void all_test()
  {
    TestRunner tr;
    tr.RunTest(test_incorrect_parameters_in_scale_csh,
        std::invalid_argument(""),"test_incorrect_parameters_in_scale_csh");
    tr.RunTest(test_invalid_index_csh, std::out_of_range(""), "test_invalid_index_csh");
    tr.RunTest(test_invalid_argument_added_shape,
        std::invalid_argument(""), "test_invalid_argument_added_shape");
    tr.RunTest(test_invalid_argument_deleted_shape,
        std::out_of_range(""), "test_invalid_argument_deleted_shape");
    tr.RunTest(test_move_composite_shape, "test_move_composite_shape");
    tr.RunTest(test_area_in_move_composite_shape, "test_area_in_move_composite_shape");
    tr.RunTest(test_get_area_in_scale, "test_get_area_in_scale");
    tr.RunTest(test_area_at_addition, "test_area_at_addition");
    tr.RunTest(test_get_frame_rect, "test_get_frame_rect");
    tr.CheckFails();
  }
}

int main()
{
  maksimova::all_test();
  return 0;
}
