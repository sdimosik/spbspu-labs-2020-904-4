#include<iostream>
#include <list>

const int MAX_VALUE = 20;
const int MIN_VALUE = 1;
const int MAX_COUNT = 20;

void specialOutputOfList(std::list<int>::const_iterator beginIt, std::list<int>::const_iterator endIt)
{
  std::cout << *beginIt;
  if (beginIt != --endIt)
  {
    std::cout << " " << *endIt << " ";
    if (++beginIt != endIt)
    {
      specialOutputOfList(beginIt, endIt);
    }
  }
}

void task2()
{
  std::list<int> list;
  int inputValue = 0;
  while ((std::cin >> inputValue) || !std::cin.eof())
  {
    if (!std::cin.eof() && std::cin.fail())
    {
      throw std::iostream::failure("Invalid characters passed");
    }
    if (list.size() == MAX_COUNT)
    {
      throw std::runtime_error("Too many queue elements");
    }
    if ((inputValue < MIN_VALUE) || (inputValue > MAX_VALUE))
    {
      throw std::out_of_range("Value ​​is outside the acceptable range");
    }
    list.push_back(inputValue);
  }
  if (!list.empty())
  {
    specialOutputOfList(list.cbegin(), list.cend());
    std::cout << "\n";
  }
}

