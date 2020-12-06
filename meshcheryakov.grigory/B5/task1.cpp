#include <iostream>
#include <unordered_set>
#include <iterator>
#include <string>
#include <algorithm>

void task1()
{
  std::unordered_set<std::string> words((std::istream_iterator<std::string>(std::cin)), std::istream_iterator<std::string>());

  if ((!std::cin.eof()) && (std::cin.fail()))
  {
    throw std::invalid_argument("Fail while reading!\n");
  }

  std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}

