#include <forward_list>
#include <vector>

#include "output.hpp"
#include "sort.hpp"

void task1(const char* direction)
{

  std::vector<int> vectorBracket;
  int num = 0;

  while (std::cin >> num)
  {
    vectorBracket.push_back(num);
  }

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::ios_base::failure("Fail while reading data.");
  }

  std::function<bool(int, int)> dir = getDirection<int>(direction);

  if (vectorBracket.empty())
  {
    return;
  }


  std::vector<int> vectorAt = vectorBracket;
  std::forward_list<int> listIt(vectorBracket.begin(), vectorBracket.end());

  selectionSort<accessUsingOperator>(vectorBracket, dir); 
  selectionSort<accessUsingAt>(vectorAt, dir); 
  selectionSort<accessUsingIterator>(listIt, dir);

  print(vectorBracket);
  print(vectorAt);
  print(listIt);
}
