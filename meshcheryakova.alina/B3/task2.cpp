#include "factorial_container.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>

void task_2()
{
  factorialContainer container;

  std::copy(container.begin(), container.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << "\n";

  std::reverse_copy(container.begin(), container.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << "\n";
}

