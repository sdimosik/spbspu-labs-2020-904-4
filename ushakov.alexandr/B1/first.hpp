#include <iostream>
#include <vector>
#include <forward_list>
#include "sort.hpp"
#include "print.hpp"
#include "detail.hpp"
#include "indexAccess.hpp"
#include "atAccess.hpp"

void firstTask(const char *sortingType)
{
  auto compare = detail::getCompare<std::vector<long>::value_type>(sortingType);
  std::vector<long> vector;
  int integer;

  while (std::cin >> integer)
  {
    vector.push_back(integer);
  }

  if (!std::cin.eof() && !std::cin.good())
  {
    throw std::ios_base::failure("Fail with reading data!");
  }

  if (vector.empty())
  {
    return;
  }

  std::vector<long> vectorIndex = vector;

  collectionSort<IndexAccess>(vectorIndex, compare);
  print(vectorIndex);

  std::vector<long> vectorAt = vector;
  collectionSort<AtAccess>(vectorAt, compare);
  print(vectorAt);

  std::forward_list<long> listIt(vector.begin(), vector.end());
  collectionSort<Iterator>(listIt, compare);
  print(listIt);
}
