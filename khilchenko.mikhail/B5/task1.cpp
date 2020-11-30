#include <iostream>
#include <iterator>
#include <unordered_set>

void task1()
{
  std::unordered_set<std::string> words(std::istream_iterator<std::string>(std::cin),
      std::istream_iterator<std::string>());

  if(!std::cin.eof() && std::cin.fail())
  {
    throw std::runtime_error("Error in reading data in task1");
  }

  std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}
