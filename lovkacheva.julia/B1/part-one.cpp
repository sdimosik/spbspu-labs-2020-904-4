#include "parts.hpp"
#include <vector>
#include <forward_list>
#include <functional>
#include "detail.hpp"
#include "bubble-sort.hpp"
#include "print-contents.hpp"

void lovkacheva::partOne(std::string order)
{
  std::function<bool(int, int)> compare = detail::getCompare<int>(order);
  std::vector<int> firstVector;
  int element = 0;
  while (std::cin >> element >> std::ws)
  {
    firstVector.push_back(element);
  }
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Input error");
  }
  if (firstVector.empty())
  {
    return;
  }
  std::vector<int> secondVector(firstVector);
  std::forward_list<int> list(firstVector.begin(), firstVector.end());

  bubbleSort<std::vector<int>, IndexOperatorAccess<std::vector<int>>>(firstVector, compare);
  bubbleSort<std::vector<int>, AtAccess<std::vector<int>>>(secondVector, compare);
  bubbleSort<std::forward_list<int>, IteratorAccess<std::forward_list<int>>>(list, compare);

  printContents(firstVector);
  printContents(secondVector);
  printContents(list);
}
