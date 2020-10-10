#include <iostream>
#include <vector>
#include <forward_list>
#include "print.hpp"
#include "sort.hpp"

void task1(char *argv)
{
  std::function<bool(int, int)> compare = getDirection<int>(argv);
  std::vector<int> vector;
  int date;
  while (std::cin >> date)
  {
    vector.push_back(date);
  }

  if (!std::cin.eof() && !std::cin.good())
  {
    throw std::runtime_error("Error: failed to read!\n");
  }

  if (vector.empty())
  {
    return;
  }

  std::vector<int> vector1(vector);
  std::forward_list<int> list(vector.begin(), vector.end());

  sort(vector, IndexReceive<std::vector<int>>(), compare);
  sort(vector1, AtReceive<std::vector<int>>(), compare);
  sort(list, IteratorReceive<std::forward_list<int>>(), compare);

  print(vector);
  std::cout << '\n';
  print(vector1);
  std::cout << '\n';
  print(list);

}
