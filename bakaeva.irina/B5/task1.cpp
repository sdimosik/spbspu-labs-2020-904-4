#include <iostream>
#include <unordered_set>
#include <string>
#include <iterator>

using in = std::istream_iterator<std::string>;
using out = std::ostream_iterator<std::string>;

void task1()
{
  std::unordered_set<std::string> set{in(std::cin), in()};

  if ((!std::cin.eof()) && (std::cin.fail()))
  {
    throw std::invalid_argument("Error by reading data!");
  }

  std::copy(set.begin(), set.end(), out(std::cout, "\n"));
}
