#include <iterator>
#include <vector>
#include <algorithm>
#include <functional>
#include "geometric-figures.hpp"

void task2()
{
  std::vector<Shape::ShapePtr> shapeArr(std::istream_iterator<Shape::ShapePtr>(std::cin), std::istream_iterator<Shape::ShapePtr>{});

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::runtime_error("Incorrect input of shape");
  }

  std::cout << "Original:\n";
  std::copy(shapeArr.begin(), shapeArr.end(), std::ostream_iterator<Shape::ShapePtr>(std::cout, "\n"));

  std::cout << "Left-Right:\n";
  std::sort(shapeArr.begin(), shapeArr.end(), std::bind(&Shape::isMoreLeft, std::bind(&Shape::ShapePtr::operator*, std::placeholders::_1), std::bind(&Shape::ShapePtr::operator*, std::placeholders::_2)));
  std::copy(shapeArr.begin(), shapeArr.end(), std::ostream_iterator<Shape::ShapePtr>(std::cout, "\n"));

  std::cout << "Right-Left:\n";
  std::reverse(shapeArr.begin(), shapeArr.end());
  std::copy(shapeArr.begin(), shapeArr.end(), std::ostream_iterator<Shape::ShapePtr>(std::cout, "\n"));

  std::cout << "Top-Bottom:\n";
  std::sort(shapeArr.begin(), shapeArr.end(), std::bind(&Shape::isUpper, std::bind(&Shape::ShapePtr::operator*, std::placeholders::_1), std::bind(&Shape::ShapePtr::operator*, std::placeholders::_2)));
  std::copy(shapeArr.begin(), shapeArr.end(), std::ostream_iterator<Shape::ShapePtr>(std::cout, "\n"));

  std::cout << "Bottom-Top:\n";
  std::reverse(shapeArr.begin(), shapeArr.end());
  std::copy(shapeArr.begin(), shapeArr.end(), std::ostream_iterator<Shape::ShapePtr>(std::cout, "\n"));
}

