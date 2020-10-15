#include <iostream>
#include <stdexcept>
#include <list>
#include <iterator>

const int MAX = 20;
const int MIN = 1;
const int MAX_SIZE = 20;

void task2()
{
  std::list<int> list;
  int current;
  while ((std::cin >> current) && (list.size() < MAX_SIZE))
  {
    if ((current <= MAX) && (current >= MIN))
    {
      list.push_back(current);
    }
    else
    {
      throw std::invalid_argument("The entered number is out of range");
    }
  }
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::invalid_argument("Not an integer number in task 2");
  }
  if ((list.size() == MAX_SIZE) && (!std::cin.eof()))
  {
    throw std::invalid_argument("More than 20 numbers entered");
  }
  if (list.empty())
  {
    return;
  }
  std::list<int>::iterator begin = list.begin();
  std::list<int>::iterator end = list.end();
  while (begin != end) 
  {
    std::cout << *begin << " ";
    begin++;
    if (begin == end)
    {
      break;
    }
    end--;
    std::cout << *end << " ";
  }
  std::cout << '\n';
}
