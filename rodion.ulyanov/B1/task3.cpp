#include <iostream>
#include <vector>
#include "print.hpp"

void task3()
{
  std::vector<int> vector;

  int input;
  while (std::cin >> input)
  {
    if (input == 0)
    {
      break;
    }
    vector.push_back(input);
  }

  if (!std::cin.good() && !std::cin.eof())
  {
    throw std::runtime_error("Unable to read. Invalid input");
  }

  if (vector.empty())
  {
    return;
  }

  if (input != 0)
  {
    throw std::invalid_argument("Last number must be zero \n");
  }

  auto last_elem = vector.back();

  if (last_elem == 1)
  {
    auto i = vector.begin();
    while (i < vector.end())
    {
      if (*i % 2 == 0)
      {
        i = vector.erase(i);
      } else
      {
        i++;
      }
    }
  } else if (last_elem == 2)
  {
    auto i = vector.begin();
    while (i < vector.end())
    {
      if (*i % 3 == 0)
      {
        i++;
        i = vector.insert(i, 3, 1);
        i += 3;
      } else
      {
        i++;
      }
    }
  }
  print(vector, " ");
}
