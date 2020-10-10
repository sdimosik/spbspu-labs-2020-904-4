#ifndef THIRDTASK_HPP
#define THIRDTASK_HPP

#include <iostream>
#include <vector>
#include "print.hpp"

void thirdTask()
{
  std::vector<int> vector;
  int number = -1;

  while(std::cin >> number)
  {
    if (number == 0)
    {
      break;
    }
    vector.push_back(number);
  }

  if(!std::cin.good() && !std::cin.eof())
  {
    throw std::ios_base::failure("Fail with read number!");
  }

  if(vector.empty())
  {
    return;
  }

  if(number != 0)
  {
    throw std::ios_base::failure("Fail with read number!");
  }

  if (*vector.rbegin() == 1)
  {
    for (auto it = vector.begin(); it != vector.end();)
    {
      if (*it % 2 == 0)
      {
        it = vector.erase(it);
        continue;
      }
      ++it;
    }
  }
  else if (*vector.rbegin() == 2)
  {
    for (auto it = vector.begin(); it != vector.end(); )
    {
      if (*it % 3 == 0)
      {
        it = vector.insert(++it, 3, 1);
        it += 3;
        continue;
      }
      ++it;
    }
  }
  print(vector);
}

#endif
