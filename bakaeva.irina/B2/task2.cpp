#include <iostream>
#include <list>

void printElem(std::list<int>::iterator directIter, std::list<int>::iterator reverseIter);

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
      throw std::invalid_argument("Numbers must be no more than 20!");
    }
    list.push_back(number);
  }

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::invalid_argument("Error by reading data!\n");
  }

  if (list.empty())
  {
    return;
  }

  auto directIter = list.begin();
  auto reverseIter = --list.end();
  printElem(directIter, reverseIter);
  std::cout << '\n';
}

void printElem(std::list<int>::iterator directIter, std::list<int>::iterator reverseIter)
{
  if (std::distance(directIter, reverseIter) == 0)
  {
    std::cout << *directIter << ' ';
    return;
  }

  if (std::distance(directIter, reverseIter) == 1)
  {
    std::cout << *directIter << ' ' << *reverseIter << ' ';
    return;
  }

  std::cout << *directIter << ' ' << *reverseIter << ' ';
  ++directIter;
  --reverseIter;
  printElem(directIter, reverseIter);
}
