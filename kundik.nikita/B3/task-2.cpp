#include <iostream>
#include <algorithm>

#include "factorial.hpp"

void task2()
{
  Container factorial;
  std::copy(factorial.begin(), factorial.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << '\n';
  std::reverse_copy(factorial.begin(), factorial.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << '\n';
}
