#include <iostream>
#include <stdexcept>
#include <string>
#include "circle.hpp"
#include "rectangle.hpp"


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

  void test_width_in_move1 ()
  {
    Rectangle rec(12.5, 15.23, point_t{2.3, 4.5});
    double width = rec.get_width();
    rec.move(point_t{3.3, 5.6});
    AssertEqual(width, rec.get_width(), std::to_string(__LINE__) + ", in file " + __FILE__);
  }

  void test_width_in_move2 ()
  {
    Rectangle rec(1.15, 6.3, point_t{15.3, 12.4});
    double  width = rec.get_width();
    rec.move(2.5, 2.5);
    AssertEqual(width, rec.get_width(), std::to_string(__LINE__) + ", in file " + __FILE__);
  }

  void test_height_in_move1 ()
  {
    Rectangle rec(12.5, 15.23, point_t{2.3, 4.5});
    double height = rec.get_height();
    rec.move(point_t{3.3, 5.6});
    AssertEqual(height, rec.get_height(), std::to_string(__LINE__) + ", in file " + __FILE__);
  }

  void test_height_in_move2 ()
  {
    Rectangle rec(1.15, 6.3, point_t{15.3, 12.4});
    double  height = rec.get_height();
    rec.move(2.5, 2.5);
    AssertEqual(height, rec.get_height(), std::to_string(__LINE__) + ", in file " + __FILE__);
  }

  void test_area_in_move1 ()
  {
    Rectangle rec(12.5, 15.23, point_t{2.3, 4.5});
    double area = rec.getArea();
    rec.move(point_t{3.3, 5.6});
    AssertEqual(area, rec.getArea(), std::to_string(__LINE__) + ", in file " + __FILE__);
  }

  void test_area_in_move2 ()
  {
    Rectangle rec(1.15, 6.3, point_t{15.3, 12.4});
    double area = rec.getArea();
    rec.move(2.5, 2.5);
    AssertEqual(area , rec.getArea(), std::to_string(__LINE__) + ", in file " + __FILE__);
  }

  void test_area_in_move3 ()
  {
    Circle circ (13.4, point_t{13.4, 12.64});
    double area = circ.getArea();
    circ.move(point_t{12.3, 14.5});
    AssertEqual(area, circ.getArea(), std::to_string(__LINE__) + ", in file " + __FILE__);
  }

  void test_area_in_move4 ()
  {
    Circle circ (13.4, point_t{13.4, 12.64});
    double area = circ.getArea();
    circ.move(2.14, 3.2);
    AssertEqual(area, circ.getArea(), std::to_string(__LINE__) + ", in file " + __FILE__);
  }

  void test_radius_in_move1 ()
  {
    Circle circ (22.3, point_t{16.2, 12.3});
    double radius = circ.getRadius();
    circ.move(point_t{12.3, 16.42});
    AssertEqual(radius, circ.getRadius(), std::to_string(__LINE__) + ", in file " + __FILE__);
  }

  void test_radius_in_move2 ()
  {
    Circle circ (16.44, point_t{43.2, 32.4});
    double radius = circ.getRadius();
    circ.move(12.3, 14.14);
    AssertEqual(radius, circ.getRadius(),std::to_string(__LINE__) + ", in file " + __FILE__);
  }

  void test_area_in_scale1 ()
  {
    Rectangle rec (12.3, 15.4, point_t{2.3, 4.5});
    double area = rec.getArea();
    double inaccuracy = 0.0000001;
    double  coefficient = 2;
    rec.scale(coefficient);
    Assert(((area * coefficient * coefficient) < (rec.getArea() + inaccuracy)
        && (area * coefficient * coefficient) > (rec.getArea() - inaccuracy)),
           std::to_string(__LINE__) + ", in file " + __FILE__);
  }

  void test_area_in_scale2 ()
  {
    Circle circ (22.4, point_t{12.3, 2.4});
    double area = circ.getArea();
    double inaccuracy = 0.0000001;
    double  coefficient = 4;
    circ.scale(coefficient);
    Assert(((area * coefficient * coefficient) < (circ.getArea() + inaccuracy)
        && (area * coefficient * coefficient) > (circ.getArea() - inaccuracy)),
           std::to_string(__LINE__) + ", in file " + __FILE__);
  }

  void test_incorrect_parameters_in_scale1 ()
  {
    Rectangle rec (22.4, 12.3, point_t{12.3, 22.4});
    rec.scale(-2);
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
    tr.RunTest(test_height_in_move1, "test_height_in_move1");
    tr.RunTest(test_height_in_move2, "test_height_in_move2");
    tr.RunTest(test_width_in_move1, "test_width_in_move1");
    tr.RunTest(test_width_in_move2, "test_width_in_move2");
    tr.RunTest(test_area_in_move1, "test_area_in_move1");
    tr.RunTest(test_area_in_move2, "test_area_in_move2");
    tr.RunTest(test_area_in_move3, "test_area_in_move3");
    tr.RunTest(test_area_in_move4, "test_area_in_move4");
    tr.RunTest(test_radius_in_move1, "test_radius_in_move1");
    tr.RunTest(test_radius_in_move2, "test_radius_in_move2");
    tr.RunTest(test_area_in_scale1, "test_area_in_scale1");
    tr.RunTest(test_area_in_scale2, "test_area_in_scale2");
    tr.RunTest(test_incorrect_parameters_in_scale1, std::invalid_argument(""), "test_incorrect_parameters_in_scale1");
    tr.CheckFails();
  }
}

int main()
{
  maksimova::all_test();
  return 0;
}
