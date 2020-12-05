#include <iostream>
#include <unordered_set>
#include <iterator>

void task_1()
{
  std::unordered_set<std::string> container{ std::istream_iterator<std::string>(std::cin),
                                                  std::istream_iterator<std::string>() };
  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::runtime_error("fail in reading stream! \n");
  }
  std::copy(container.begin(), container.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

}
