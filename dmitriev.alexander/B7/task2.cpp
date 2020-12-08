#include <iterator>
#include <functional>
#include <vector>
#include <algorithm>
#include "shape.hpp"

void task2()
{
  std::vector<std::shared_ptr<Shape>>
    vector(std::istream_iterator<std::shared_ptr<Shape>>(std::cin), std::istream_iterator<std::shared_ptr<Shape>>{});

  if ((!std::cin.eof()) && (std::cin.fail()))
  {
    throw std::ios::failure("Fail while reading data!");
  }

  std::cout << "Original:" << std::endl;
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));

  auto lhs = std::bind(&std::shared_ptr<Shape>::operator*, std::placeholders::_1);
  auto rhs = std::bind(&std::shared_ptr<Shape>::operator*, std::placeholders::_2);

  std::sort(vector.begin(), vector.end(), std::bind(&Shape::isMoreLeft, lhs, rhs));

  std::cout << "Left-Right:" << std::endl;
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));

  std::reverse(vector.begin(), vector.end());
  std::cout << "Right-Left:" << std::endl;
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));

  std::sort(vector.begin(), vector.end(), std::bind(&Shape::isUpper, lhs, rhs));

  std::cout << "Top-Bottom:" << std::endl;
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));

  std::reverse(vector.begin(), vector.end());
  std::cout << "Bottom-Top:" << std::endl;
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));
}
