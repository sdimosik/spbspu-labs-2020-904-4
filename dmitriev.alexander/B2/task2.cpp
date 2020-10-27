#include <list>
#include <iostream>

void task2()
{
  std::list<int> list;
  int number;
  while (std::cin >> number)
  {
    if (number < 1 || number > 20)
    {
      throw std::invalid_argument("Number must be between 1 and 20!");
    }
    if (list.size() >= 20)
    {
      throw std::invalid_argument("List size be less 20!");
    }
    list.push_back(number);
  }

  if (!std::cin.good() && !std::cin.eof())
  {
    throw std::ios_base::failure("Error while reading occurred!\n");
  }

  if (list.empty())
  {
    return;
  }
  auto beginIter = list.begin();
  auto endIter = --list.end();
  if (list.size() % 2 != 0)
  {
    while (beginIter != endIter)
    {
      std::cout << *beginIter++ << " " << *endIter-- << " ";
    }
    std::cout << *beginIter++;
  } else
  {
    auto nextIter = beginIter;
    while (++nextIter != endIter)
    {
      std::cout << *beginIter++ << " " << *endIter-- << " ";
      nextIter = beginIter;
    }
    std::cout << *beginIter << " " << *endIter;
  }
  std::cout << std::endl;
}
