#include "parts.hpp"
#include <list>
#include <iostream>

namespace lovkacheva
{
  using IntList = std::list<int>;
  using It = IntList::iterator;

  void output(It first, It second)
  {
    if (first == second)
    {
      std::cout << '\n';
    }
    else if (std::next(first) == second)
    {
      std::cout << *first << '\n';
    }
    else
    {
      --second;
      std::cout << *first << ' ' << *second << ' ';
      output(std::next(first), second);
    }
  }
}

void lovkacheva::partTwo()
{
  const size_t MAX_SIZE = 20;
  const size_t MAX_VALUE = 20;
  const size_t MIN_VALUE = 1;
  IntList list;
  unsigned int element = 0;
  while (std::cin >> element)
  {
    list.push_back(element);
    if (element < MIN_VALUE || element > MAX_VALUE)
    {
      throw std::invalid_argument("The elements of the list must fall within range 1..20, "
          + std::to_string(element) + " does not");
    }
  }
  if (list.size() > MAX_SIZE)
  {
    throw std::runtime_error("Too many values");
  }
  if (std::cin.fail() && !std::cin.eof())
  {
      throw std::runtime_error("Invalid input");
  }
  if (!list.empty())
  {
    output(list.begin(), list.end());
  }
}
