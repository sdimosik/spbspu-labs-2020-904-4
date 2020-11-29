#include <unordered_set>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <stdexcept>

void task1()
{
  std::unordered_set<std::string> wordsContainer{ std::istream_iterator<std::string>(std::cin),
      std::istream_iterator<std::string>() };
  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::runtime_error("Error while reading");
  }
  std::copy(wordsContainer.begin(), wordsContainer.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}
