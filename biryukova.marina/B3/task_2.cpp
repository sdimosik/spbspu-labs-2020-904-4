#include <iterator>
#include <iostream>
#include <algorithm>
#include <cstddef>
#include "factorial.hpp"

void task2()
{
  Factorial factorial;
  std::copy(factorial.begin(), factorial.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << '\n';
  std::reverse_copy(factorial.begin(), factorial.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << '\n';
}
