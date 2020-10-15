#include <list>
#include <iostream>
#include <stdexcept>

const size_t INPUT_MIN_NUMBER = 1;
const size_t INPUT_MAX_NUMBER = 20;
const size_t LIST_MAX_SIZE = 20;

void printList(std::list<size_t>& list);

void task2()
{
  std::list<size_t> list;
  size_t count = 0;
  size_t element = 0;
  while (std::cin >> element)
  {
    if (count >= LIST_MAX_SIZE)
    {
      throw std::invalid_argument("Too many values in input");
    }
    if ((element >= INPUT_MIN_NUMBER) && (element <= INPUT_MAX_NUMBER))
    {
      list.push_back(element);
    }
    else
    {
      throw std::invalid_argument("Number must be integer between 1 and 20");
    }
    ++count;
  }

  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error of reading");
  }

  printList(list);
}

void printList(std::list<size_t>& list)
{
  if (list.empty())
  {
    return;
  }
  std::list<size_t>::iterator current = list.begin();
  std::list<size_t>::reverse_iterator reverseCurrent = list.rbegin();
  while (std::distance(current, reverseCurrent.base()) > 2)
  {
    std::cout << *current++ << ' ' << *reverseCurrent++ << ' ';
  }
  if (std::distance(current, reverseCurrent.base()) == 2)
  {
    std::cout << *current++ << ' ' << *reverseCurrent++ << '\n';
  }
  if (std::distance(current, reverseCurrent.base()) == 1)
  {
    std::cout << *current++ << '\n';
  }
}
