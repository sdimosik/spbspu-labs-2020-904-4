#ifndef SPBSPU_LABS_2020_904_4_SORT_HPP
#define SPBSPU_LABS_2020_904_4_SORT_HPP

#include <functional>
#include <cstring>
#include "access.hpp"

template<typename T>
std::function<bool(const T, const T)> getCompare(const char *direction)
{
  if (std::strcmp(direction, "ascending") == 0)
  {
    return std::less<const T>();
  }
  if (std::strcmp(direction, "descending") == 0)
  {
    return std::greater<const T>();
  }
  throw std::invalid_argument("Invalid sort\n");
}

template<template<class> class Access, class T>
void sort(T &data, std::function<bool(typename T::value_type, typename T::value_type)> compare)
{
  auto begin = Access<T>::begin(data);
  auto end = Access<T>::end(data);
  while (begin != end)
  {
    auto j = begin;
    while (j != end)
    {
      typename T::value_type &left = Access<T>::getElement(data, j);
      typename T::value_type &right = Access<T>::getElement(data, begin);
      if (compare(left, right))
      {
        std::swap(left, right);
      }
      j++;
    }
    begin++;
  }
}

#endif
