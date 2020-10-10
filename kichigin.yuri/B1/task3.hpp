#ifndef TASK3
#define TASK3
#include <iostream>
#include <vector>
#include "print.hpp"

void task3()
{
  std::vector<int> vector;
  int number = 0;
  while (std::cin >> number)
  {
    if (std::cin.fail())
    {
      throw std::invalid_argument("Invalid data in task 3");
    }
    if (number == 0)
    {
      break;
    }
    vector.push_back(number);
  }

  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::invalid_argument("Invalid data in task 3");
  }

  if (number != 0)
  {
    throw std::invalid_argument("Missing zero");
  }

  if (vector.empty())
  {
    return;
  }

  if (vector.back() == 1)
  {
    std::vector<int>::iterator i = vector.begin();
    while (i != vector.end())
    {
      if (*i % 2 == 0)
      {
        i = vector.erase(i);
      }
      else
      {
        ++i;
      }
    }
  }

  if (vector.back() == 2)
  {
    std::vector<int>::iterator i = vector.begin();
    while (i != vector.end())
    {
      if (*i % 3 == 0)
      {
        i = vector.insert(++i, 3, 1) + 3;
      }
      else
      {
        ++i;
      }
    }
  }

  print(vector, " ");
}
#endif // !TASK3
