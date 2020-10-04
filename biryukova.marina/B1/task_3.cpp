#include <vector>
#include <iostream>
#include "tasks.hpp"

void task3()
{
  std::vector<int> array{};
  int current = 0;
  while (std::cin >> current) 
  {
    if (current == 0) 
    {
      break;
    }
    array.push_back(current);
  }
  if (std::cin.fail() && !std::cin.eof())
    {
      throw std::runtime_error("Not an integer number in task 3");
    }
  if (current != 0)
  {
    throw std::runtime_error("No '0' at the end of the sequence in task 3");
  }
  if (array.empty()) 
  {
    return;
  }
  if (array.back() == 1) 
  {
    std::vector<int>::iterator iter = array.begin();
    while (iter != array.end()) 
    {
      if (*iter % 2 == 0) 
      {
        iter = array.erase(iter);
      }
      else 
      {
        iter++;
      }
    }
  }
  else if (array.back() == 2) 
  {
    std::vector<int>::iterator iter = array.begin();
    while (iter != array.end()) 
    {
      if (*iter % 3 == 0) 
      {
        ++iter;
        iter = array.insert(iter, 3, 1);
        iter += 3;
      }
      else 
      {
        iter++;
      }
    }
  }
  print(array, " ");
}
