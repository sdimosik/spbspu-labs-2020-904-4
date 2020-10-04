#ifndef B1_SORT_HPP
#define B1_SORT_HPP

#include <functional>
#include <cstring>
#include "accessingElements.hpp"

template<typename T>
std::function<bool(const T, const T)> getComparisonSign(const char *orientation)
{
  if (orientation != nullptr)
  {
    if (std::strcmp(orientation, "ascending") == 0)
    {
      return std::less<const T>();
    }
    if (std::strcmp(orientation, "descending") == 0)
    {
      return std::greater<const T>();
    }
    throw std::invalid_argument("Unknown orientation!\n");
  }

  throw std::invalid_argument("Pointer is nullptr!\n");
}

template<template<class> class Access, class T>
void sort(T &container, std::function<bool(const typename T::value_type, const typename T::value_type)> compare)
{
  auto i = Access<T>::begin(container);
  auto end = Access<T>::end(container);
  while (i != end)
  {
    auto j = i;
    while (j != end)
    {
      typename T::value_type &left = Access<T>::getElement(container, j);
      typename T::value_type &right = Access<T>::getElement(container, i);
      if (compare(left, right))
      {
        std::swap(left, right);
      }
      j++;
    }
    i++;
  }
}

#endif

