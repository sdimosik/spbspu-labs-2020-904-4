#include <unordered_set>
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <string>
#include <algorithm>

void task1()
{
  std::unordered_set<std::string> words{std::istream_iterator<std::string>(std::cin), 
      std::istream_iterator<std::string>()};
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error while reading in task 1");
  }
  std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}
