#include <iostream>
#include <list>

void print(std::list<int>::iterator start, std::list<int>::iterator stop);

void task2()
{
  int value = 0;
  std::list<int> list;
  const int minValue = 1;
  const int maxValue = 20;
  const size_t maxSize = 20;
  while (std::cin >> value)
  {
    if (value < minValue || value > maxValue)
    {
      throw std::invalid_argument("Error: numbers cannot be more than 20 and less than 1!");
    }

    if (list.size() >= maxSize)
    {
      throw std::invalid_argument("Error: you can add only 20 elements!");
    }
    list.push_back(value);
  }

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::invalid_argument("Error: Error: there was a problem reading the data!\n");
  }

  if (list.empty())
  {
    return;
  }

  auto startElement = list.begin();
  auto stopElement = std::prev(list.end());
  print(startElement, stopElement);
  std::cout << "\n";
}

void print(std::list<int>::iterator start, std::list<int>::iterator stop)
{
  if (start == stop)
  {
    std::cout << *start << ' ';
    return;
  }

  if (start == std::prev(stop))
  {
    std::cout << *start << ' ' << *stop << ' ';
    return;
  }

  std::cout << *start++ << ' ' << *stop-- << ' ';
  print(start, stop);
}
