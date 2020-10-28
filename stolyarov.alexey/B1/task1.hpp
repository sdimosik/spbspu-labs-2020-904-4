#ifndef TASK_1_HPP
#define TASK_1_HPP

#include <iostream>
#include <forward_list>
#include <string>
#include <vector>
#include "access.hpp"
#include "utilities.hpp"

void task1(const char* sortType)
{
  std::vector<int> vector;
  int in;

  while (std::cin >> in)
  {
    if (std::cin.fail())
    {
      throw std::invalid_argument("Task 1: Invalid data");
    }
    vector.push_back(in);
  }

  if (!std::cin.eof() && !std::cin.good())
  {
    throw std::ios_base::failure("Task 1: Reading data failure");
  }

  std::vector<int> vectorAt(vector);
  std::forward_list<int> list(vector.begin(), vector.end());

  utilities::bubbleSort<IndexAccess>(vector, utilities::compareOrder<int>(sortType));
  utilities::println(vector);

  utilities::bubbleSort<AtAccess>(vectorAt, utilities::compareOrder<int>(sortType));
  utilities::println(vector);

  utilities::bubbleSort<IteratorAccess>(list, utilities::compareOrder<int>(sortType));
  utilities::println(list);
}

#endif
