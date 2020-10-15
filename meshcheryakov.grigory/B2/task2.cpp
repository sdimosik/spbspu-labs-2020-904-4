#include <iostream>
#include <stdexcept>
#include <list>

template<typename T>
void printList(typename std::list<T>::iterator begin, typename std::list<T>::iterator end)
{
  if (begin == end)
  {
    std::cout << '\n';
    return;
  }

  if(begin == std::prev(end))
  {
    std::cout << *begin << '\n';
    return;
  }

  std::cout << *begin++ << ' ' << *std::prev(end--) << ' ';
  printList<T>(begin, end);
}

void task2()
{
  std::list<int> list;
  int number;
  while (std::cin >> number)
  {
    if (number < 1 || number > 20)
    {
      throw std::invalid_argument("Number cannot be less than 1 and more than 20");
    }
    if (list.size() >= 20)
    {
      throw std::invalid_argument("Numbers cannot be more than 20");
    }
    list.push_back(number);
  }

  if (!std::cin.good() && !std::cin.eof())
  {
    throw std::ios_base::failure("Fail with reading data!");
  }

  if (list.empty())
  {
    return;
  }

  printList<int>(list.begin(), list.end());
}
