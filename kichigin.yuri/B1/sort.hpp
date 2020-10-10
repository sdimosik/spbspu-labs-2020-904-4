#ifndef SORT
#define SORT

#include <string.h>
#include <stdexcept>
#include <functional>
#include"access.h"

enum class Direction
{
  ascending,
  descending
};

bool isDirectionStringCorrect(const char* direction)
{
  return (strcmp(direction, "ascending") == 0 || strcmp(direction, "descending") == 0);
}

template <class T>
std::function<bool(const T, const T)> getCompare(const Direction direction)
{
  if (direction == Direction::ascending)
  {
    return std::greater<const T>();
  }
  else if (direction == Direction::descending)
  {
    return std::less<const T>();
  }
  throw std::invalid_argument("Unknown direction");
}

template <template <class> class Access, class container>
void bubbleSort(container& collection, Direction direction)
{
  const auto begin = Access<container>::begin(collection);
  const auto end = Access<container>::end(collection);
  std::function<bool(typename container::value_type, typename container::value_type)> compare 
    = getCompare<typename container::value_type>(direction);

  for (auto i = begin; i != end; ++i)
  {
    for (auto j = i; j != end; ++j)
    {
      if (compare(Access<container>::getElement(collection, i), Access<container>::getElement(collection, j)))
      {
        std::swap(Access<container>::getElement(collection, i), Access<container>::getElement(collection, j));
      }
    }
  }
}
#endif // !SORT
