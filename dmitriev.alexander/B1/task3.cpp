#include <vector>
#include <iostream>
#include "extensions.hpp"

void task3()
{
  std::vector<int> vector;

  int inputNumber = 0;

  while (std::cin >> inputNumber && inputNumber)
  {
    vector.push_back(inputNumber);
  }

  if (!std::cin.good() && !std::cin.eof())
  {
    throw std::ios_base::failure("Error while reading occurred!\n");
  }

  if (vector.empty())
  {
    return;
  }

  if (inputNumber != 0)
  {
    throw std::invalid_argument("Last number must be zero!\n");
  }

  if (vector.back() == 1 || vector.back() == 2)
  {
    auto iterator = vector.begin();
    if (vector.back() == 1)
    {
      while (iterator != vector.end())
      {
        if (*iterator % 2 == 0)
        {
          iterator = vector.erase(iterator);
        } else
        {
          iterator++;
        }
      }
    } else
    {
      while (iterator != vector.end())
      {
        if (*iterator % 3 == 0)
        {
          iterator = vector.insert(iterator + 1, 3, 1);
          iterator += 3;
        } else
        {
          iterator++;
        }
      }
    }
  }
  printArray(vector);
}
