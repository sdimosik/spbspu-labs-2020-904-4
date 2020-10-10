#include <iostream>
#include <vector>
#include "print.hpp"

void task3()
{
  std::vector<int> vector;
  int number = 0;
  while (std::cin >> number)
  {
    if (number == 0)
    {
      break;
    }
    vector.push_back(number);
  }

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::ios_base::failure("Error: reading data problem!\n");
  }

  if (vector.empty())
  {
    return;
  }

  if (number != 0)
  {
    throw std::invalid_argument("Error: the last number must be zero!\n");
  }

  auto last = vector.back();

  if (last == 1)
  {
    for (auto i = vector.begin(); i != vector.end();)
    {
      if (*i % 2 == 0)
      {
        i = vector.erase(i);
      }
      else
      {
        i++;
      }
    }
  }

  if (last == 2)
  {
    for (auto i = vector.begin(); i != vector.end();)
    {
      if (*i % 3 == 0)
      {
        i = vector.insert(i + 1, 3, 1);
        i += 3;
      }
      else
      {
        i++;
      }
    }
  }

  print(vector);
}
