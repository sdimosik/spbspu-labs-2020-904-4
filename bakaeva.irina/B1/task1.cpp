#include <iostream>
#include <vector>
#include <forward_list>
#include "sort.hpp"
#include "printData.hpp"

void task1(const char *orientation)
{
  std::function<bool(int, int)> compare = getComparisonSign<int>(orientation);

  std::vector<int> vector1;
  int number;
  while (std::cin >> number)
  {
    vector1.push_back(number);
  }

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::runtime_error("Error by reading data!\n");
  }

  if(vector1.empty())
  {
    return;
  }

  std::vector<int> vector2(vector1);
  std::forward_list<int> list(vector1.begin(), vector1.end());

  sort<AccessByBrackets>(vector1, compare);
  sort<AccessByAt>(vector2, compare);
  sort<AccessByIterator>(list, compare);

  printData(vector1, " ");
  std::cout << '\n';
  printData(vector2, " ");
  std::cout << '\n';
  printData(list, " ");
}
