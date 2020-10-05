#include "parts.hpp"
#include <vector>
#include "print-contents.hpp"

void lovkacheva::partThree()
{
  std::vector<int> vector;
  int element = 1;
  while ((std::cin >> std::ws >> element) && !std::cin.eof() && element != 0)
  {
    vector.push_back(element);
  }
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Input error");
  }
  if (vector.empty())
  {
    return;
  }
  if (element != 0)
  {
    throw std::runtime_error("The end of the sequence must be indicated by 0");
  }
  using It = std::vector<int>::iterator;
  int& last = vector.back();
  if (last == 1)
  {
    for (It i = vector.begin(); i != vector.end();)
    {
      if (*i % 2 == 0)
      {
        i = vector.erase(i);
      }
      else
      {
        ++i;
      }
    }
  }
  else if (last == 2)
  {
    size_t spaceNeeded = 0;
    for (It i = vector.begin(); i != vector.end(); ++i)
    {
      if (*i % 3 == 0)
      {
        spaceNeeded += 3;
      }
    }
    vector.reserve(vector.size() + spaceNeeded);
    for (It i = vector.begin(); i != vector.end(); ++i)
    {
      if (*i % 3 == 0)
      {
        i = vector.insert(std::next(i), 3, 1);
        std::advance(i, 2);
      }
    }
  }
  printContents(vector);
}
