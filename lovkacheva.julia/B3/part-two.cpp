#include "parts.hpp"
#include <iterator>
#include <iostream>
#include <algorithm>
#include "factorial.hpp"
void lovkacheva::partTwo()
{
  Factorial factorial;
  std::ostream_iterator<int> outIt(std::cout, " ");
  std::copy(factorial.begin(), factorial.end(), outIt);
  std::cout << '\n';
  std::reverse_copy(factorial.begin(), factorial.end(), outIt);
  std::cout << '\n';
}
