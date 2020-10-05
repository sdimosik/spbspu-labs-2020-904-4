#ifndef SORT_HPP
#define SORT_HPP

#include <functional>
#include <stdexcept>
#include <cstring>
#include "access.hpp"

template<typename T>
std::function<bool(const T, const T)> getDirection(const char *direction)
{
  if (direction != nullptr)
  {
    if (std::strcmp(direction, "ascending") == 0)
    {
      return std::less<const T>();
    }
    else if (std::strcmp(direction, "descending") == 0)
    {
      return std::greater<const T>();
    }
    throw std::invalid_argument("Invalid direction");
  }

  throw std::invalid_argument("Direction does not exist");
}


template <template <class T> class Access, typename T>
void selectionSort(T& collection, std::function<bool(const typename T::value_type,
    const typename T::value_type)> compare)
{
  const auto begin = Access<T>::begin(collection);
  const auto end = Access<T>::end(collection);

  for (auto i = begin; i != end; ++i)
  {
    auto temp = i;
    for (auto j = Access<T>::next(i); j != end; ++j)
    {
      if (compare(Access<T>::element(collection, j), Access<T>::element(collection, temp)))
      {
        temp = j;
      }
    }

    if (temp != i)
    {
      std::swap(Access<T>::element(collection, temp), Access<T>::element(collection, i));
    }
  }
}
#endif
