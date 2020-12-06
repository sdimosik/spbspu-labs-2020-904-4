#include <iostream>
#include <string>
#include <unordered_set>
#include <iterator>

void task1()
{
  std::unordered_set<std::string>
    list((std::istream_iterator<std::string>(std::cin)), std::istream_iterator<std::string>());

  if ((!std::cin.eof()) && (std::cin.fail()))
  {
    throw std::invalid_argument("Error while reading data!\n");
  }

  std::copy(list.begin(), list.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}
