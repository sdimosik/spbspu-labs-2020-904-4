#include <iostream>
#include <vector>
#include <forward_list>
#include "sort.hpp"
#include "print.hpp"

void task1(const char *direction)
{
  std::function<bool(int, int)> compare = getCompare<int>(direction);
  std::vector<int> input_vector;

  int data;
  while (std::cin >> data)
  {
    input_vector.push_back(data);
  }

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::runtime_error("Unable to read. Invalid input\n");
  }

  if (input_vector.empty())
  {
    return;
  }

  std::vector<int> index_vector = input_vector;
  sort<IndexAccess>(index_vector, compare);
  print(index_vector, " ");
  std::cout << '\n';

  std::vector<int> at_vector = input_vector;
  sort<AtAccess>(at_vector, compare);
  print(at_vector, " ");
  std::cout << '\n';

  std::forward_list<int> list(input_vector.begin(), input_vector.end());
  sort<IteratorAccess>(list, compare);
  print(list, " ");
}
