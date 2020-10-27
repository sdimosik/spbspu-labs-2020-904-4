#ifndef SECONDTASK_HPP
#define SECONDTASK_HPP

#include <iostream>
#include <list>
#include <string>
#include <stdexcept>

template <typename T>
void print(typename std::list<T>::iterator begin, typename std::list<T>::iterator end)
{
  if(begin == end)
  {
    std::cout << '\n';
    return;
  }
  if (begin == std::prev(end))
  {
    std::cout << *begin << '\n';
    return;
  }
  std::cout << *begin << " " << *std::prev(end) << " ";
  begin++;
  end--;
  print<int>(begin, end);
}

void secondTask()
{
  std::list<int> list;
  int number = 0;
  size_t amount = 0;

  while (std::cin >> number)
  {
    if (number < 1 || number > 20)
    {
      throw std::invalid_argument(std::string("Invalid range of numbers. Your number is ")
          += std::to_string(number));
    }
    ++amount;
    if (amount > 20)
    {
      throw std::invalid_argument("Invalid amount of numbers.");
    }
    list.push_back(number);
  }

  if(!std::cin.good() && !std::cin.eof())
  {
    throw std::ios_base::failure("Fail with read number!");
  }

  print<int>(list.begin(), list.end());
}

#endif
