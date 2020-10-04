#include <vector>
#include <iostream>
#include <forward_list>
#include "access.hpp"
#include "tasks.hpp"

void task1(const std::string& order)
{
  if ((order != "ascending") && (order != "descending"))
  {
    throw std::runtime_error("Invalid argument in task 1");
  }
  std::vector<int> array{};
  int current;
  while (std::cin >> current) 
  {
    array.push_back(current);
  }
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Not an integer number in task 1");
  }
  if (array.empty()) 
  {
    return;
  }
  std::function<bool(const int&, const int&)> comparator = getComparator<int>(order);
  std::vector<int> indexArray{array.begin(), array.end()};
  std::vector<int> atArray{array.begin(), array.end()};
  std::forward_list<int> iteratorArray{array.begin(), array.end()};

  selectionSort<IndexAccess>(indexArray, comparator);
  selectionSort<AtAccess>(atArray, comparator);
  selectionSort<IteratorAccess>(iteratorArray, comparator);

  print(indexArray, " ");
  print(atArray, " ");
  print(iteratorArray, " ");
}
