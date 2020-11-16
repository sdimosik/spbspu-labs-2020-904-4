#include "tasks.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>
#include "functions.hpp"

void task::doThirdTask()
{
  std::vector<int> vector;
  int number = 0;
  while (std::cin >> number && number != 0)
  {
    vector.push_back(number);
  }

  if (std::cin.bad())
  {
    throw std::runtime_error("Error while reading");
  }

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::invalid_argument(BAD_INPUT_NUMBERS);
  }

  if (number != 0)
  {
    throw std::invalid_argument("Incorrect input! You must stop your input with 0!");
  }

  if (vector.empty())
  {
    return;
  }

  auto iterator = vector.begin();

  if (vector.back() == 1)
  {
    while (iterator != vector.end())
    {
      if (*iterator % 2 == 0)
      {
        iterator = vector.erase(iterator);
        continue;
      }
      ++iterator;
    }
  }

  if (vector.back() == 2)
  {
    while (iterator != vector.end())
    {
      if ((*iterator % 3 == 0))
      {
        iterator = vector.insert(++iterator, 3, 1) + 3;
        continue;
      }
      ++iterator;
    }
  }
  detail::printContainer(vector);
}
