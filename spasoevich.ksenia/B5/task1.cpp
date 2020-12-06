#include <iostream>
#include <string>
#include <unordered_set>
#include <iterator>
#include <algorithm>

void task1()
{
  std::unordered_set<std::string> uoSet((std::istream_iterator<std::string>(std::cin)), std::istream_iterator<std::string>());
  std::copy(uoSet.begin(), uoSet.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}
