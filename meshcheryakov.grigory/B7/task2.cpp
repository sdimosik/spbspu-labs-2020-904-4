#include <iterator>
#include <functional>
#include <vector>
#include <algorithm>
#include "shape.hpp"

void task2()
{
  std::vector<std::shared_ptr<Shape>> vector(std::istream_iterator<std::shared_ptr<Shape>>(std::cin),
      std::istream_iterator<std::shared_ptr<Shape>>{});

  if ((!std::cin.eof()) && (std::cin.fail()))
  {
    throw std::ios::failure("Error while reading data!\n");
  }

  std::cout << "Original:\n";
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));

  std::sort(vector.begin(), vector.end(), std::bind(&Shape::isMoreLeft, std::bind(&std::shared_ptr<Shape>::operator*, std::placeholders::_1),
      std::bind(&std::shared_ptr<Shape>::operator*, std::placeholders::_2)));

  std::cout << "Left-Right:\n";
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));

  std::reverse(vector.begin(), vector.end());
  std::cout << "Right-Left:\n";
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));

  std::sort(vector.begin(), vector.end(), std::bind(&Shape::isUpper, std::bind(&std::shared_ptr<Shape>::operator*, std::placeholders::_1),
      std::bind(&std::shared_ptr<Shape>::operator*, std::placeholders::_2)));

  std::cout << "Top-Bottom:\n";
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));

  std::reverse(vector.begin(), vector.end());
  std::cout << "Bottom-Top:\n";
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));
}
