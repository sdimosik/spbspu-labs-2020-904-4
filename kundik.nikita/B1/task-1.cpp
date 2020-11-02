#include "tasks.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <forward_list>
#include "accesses.hpp"
#include "functions.hpp"

void task::doFirstTask(const char* sortDirection)
{
  std::vector<int> vectorIndex;
  int number = 0;
  while (std::cin >> number)
  {
    vectorIndex.push_back(number);
  }

  if (std::cin.bad())
  {
    throw std::runtime_error(UNKNOWN_ERROR);
  }

  if (!std::cin.eof())
  {
    throw std::invalid_argument(BAD_INPUT_NUMBERS);
  }

  std::vector<int> vectorAt(vectorIndex);
  std::forward_list<int> forwardList(vectorAt.begin(), vectorAt.end());

  std::function<bool(int, int)> compare = detail::getCompare<int>(sortDirection);

  detail::sortContainer<detail::AccessByIndex>(vectorIndex, compare);
  detail::sortContainer<detail::AccessByAt>(vectorAt, compare);
  detail::sortContainer<detail::AccessByIterator>(forwardList, compare);

  detail::printContainer(vectorIndex);
  detail::printContainer(vectorAt);
  detail::printContainer(forwardList);
}
