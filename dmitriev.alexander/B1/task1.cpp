#include <vector>
#include <forward_list>
#include "extensions.hpp"
#include "sort.hpp"

void task1(const char *typeString)
{
  std::function<bool(int, int)> compare = getComparisonType<int>(typeString);

  std::vector<int> vector;

  int number;
  while (std::cin >> number)
  {
    vector.push_back(number);
  }

  if (!std::cin.good() && !std::cin.eof())
  {
    throw std::ios_base::failure("Error while reading occurred!\n");
  }

  if (vector.empty())
  {
    return;
  }

  std::vector<int> vector2(vector);
  std::forward_list<int> list(vector.begin(), vector.end());

  sort<AccessByBrackets>(vector, compare);
  printArray(vector);
  std::cout << std::endl;
  sort<AccessByAt>(vector2, compare);
  printArray(vector2);
  std::cout << std::endl;
  sort<AccessByIterator>(list, compare);
  printArray(list);
}
