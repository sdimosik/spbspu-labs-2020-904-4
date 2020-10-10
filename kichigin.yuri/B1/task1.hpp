#ifndef TASK1
#define TASK1

#include <stdexcept>
#include <vector>
#include <forward_list>
#include <iostream>
#include "sort.hpp"
#include "print.hpp"

void task1(const char* parametr)
{
  if (!isDirectionStringCorrect(parametr))
  {
    throw std::invalid_argument("Invalid sort direction in task 1");
  }
  Direction direction = (strcmp(parametr, "ascending") == 0 ? Direction::ascending : Direction::descending);

  std::vector<int> vectorIndex;
  int number = 0;
  while (std::cin >> number)
  {
    vectorIndex.push_back(number);
  }
  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::runtime_error("Uncorrect input");
  }

  std::vector<int> vectorAt(vectorIndex);
  std::forward_list<int> list(vectorIndex.begin(), vectorIndex.end());

  bubbleSort<IndexAccess>(vectorIndex, direction);
  print(vectorIndex, " ");

  bubbleSort<AtAccess>(vectorAt, direction);
  print(vectorAt, " ");

  bubbleSort<IteratorAccess>(list, direction);
  print(list, " ");
}
#endif // !TASK1
