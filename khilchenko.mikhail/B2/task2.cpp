#include <list>
#include <iostream>
#include <exception>

void task2()
{
  std::list<int> list;

  int inputVar;
  while(std::cin >> inputVar)
  {
    if(inputVar < 1 || inputVar > 20)
    {
      throw std::invalid_argument("Integer values in the task2 must be between 1 and 20");
    }

    list.push_back(inputVar);

    if(list.size() > 20)
    {
      throw std::invalid_argument("Number of integers in the task2 must be less or equal to 20");
    }
  }

  if(std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error in reading data in task2");
  }

  std::list<int>::iterator beginIt = list.begin();
  std::list<int>::iterator endIt = list.end();

  while(beginIt != endIt)
  {
    std::cout << *beginIt << ' ';
    beginIt++;
    if(beginIt == endIt)
    {
      break;
    }
    endIt--;
    std::cout << *endIt << ' ';
  }
  std::cout << '\n';
}
