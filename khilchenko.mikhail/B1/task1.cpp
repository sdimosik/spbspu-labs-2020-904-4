#include <forward_list>
#include <exception>
#include <cstring>
#include "access.hpp"
#include "sort.hpp"
#include "print.hpp"

void task1(char* order)
{
  std::vector<int> inputVector;

  int inputVar;
  while(std::cin >> inputVar)
  {
    inputVector.push_back(inputVar);
  }

  if(!std::cin.eof())
  {
    throw std::runtime_error("Not an integer in input in task1");
  }

  std::function<bool(int, int)> compare = getCompare<int>(order);

  std::vector<int> indexVector = inputVector;
  sort<IndexAccess>(indexVector, compare);
  print(indexVector);

  std::vector<int> atVector = inputVector;
  sort<AtAccess>(atVector, compare);
  print(atVector);

  std::forward_list<int> list(inputVector.begin(), inputVector.end());
  sort<IteratorAccess>(list, compare);
  print(list);
}
