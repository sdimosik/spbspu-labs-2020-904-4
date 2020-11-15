#include "tasks.hpp"
#include <stdexcept>
#include <iostream>
#include <list>
#include "functions.hpp"

template <typename T>
void printFrontRearOrder(typename std::list<T>::iterator begin, typename std::list<T>::iterator end)
{
  if (begin == end)
  {
    std::cout << "\n";
    return;
  }

  if (begin == std::prev(end))
  {
    std::cout << *begin << '\n';
    return;
  }
  std::cout << *begin++ << ' ' << *std::prev(end--) << ' ';
  printFrontRearOrder<T>(begin, end);
}

void task::doSecondTask()
{
  size_t amount = 0;
  int number = 0;
  std::list<int> list;
  while (std::cin >> number)
  {
    if (number < 1 || number > 20)
    {
      throw std::invalid_argument("Number must be between 1 and 20!");
    }

    ++amount;
    if (amount > 20)
    {
      throw std::invalid_argument("Numbers must be no more than 20!");
    }
    list.push_back(number);
  }
  if (!std::cin.good() && !std::cin.eof())
  {
    throw std::ios_base::failure("Incorrect input! Written command is too long!");
  }

  printFrontRearOrder<int>(list.begin(), list.end());
}
