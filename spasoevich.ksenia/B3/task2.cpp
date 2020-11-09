#include <algorithm>
#include <iostream>

#include "factorial-iterator.hpp"

void task2()
{
  FactorialContainer container;

  std::copy(container.begin(), container.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << "\n";

  std::reverse_copy(container.begin(), container.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << "\n";
}

