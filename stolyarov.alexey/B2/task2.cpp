#include <list>
#include <iostream>
#include <string>
#include "commands.hpp"

void task2()
{
  int num, count = 0;
  std::list<int> list;

  while (std::cin >> num)
  {
    if (num < 1 || num > 20)
    {
      throw std::invalid_argument("Invalid argument: Number should be 1 <= num <= 20. Have: " + std::to_string(num));
    }
    count++;
    if (count > 20)
    {
      throw std::invalid_argument("Invalid count of number: Count should be 0 <= count <= 20. Have: " + std::to_string(num));
    }
    list.push_back(num);
  }

  if (!std::cin.good() && !std::cin.eof())
  {
    throw std::ios_base::failure("Task 2: Reading data failure");
  }
  commands::print<int>(list.begin(), list.end());
}
