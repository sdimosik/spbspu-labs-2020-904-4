#ifndef SORT_HPP
#define SORT_HPP

#include <functional>
#include <cstring>
#include "accessType.hpp"

template<template<class> class Access, class T>
void sort(T &container, std::function<bool(const typename T::value_type, const typename T::value_type)> compare)
{
  auto start = Access<T>::begin(container);
  auto end = Access<T>::end(container);
  for (auto i = start; i != end; i++)
  {
    for (auto j = i; j != end; j++)
    {
      typename T::value_type &left = Access<T>::getElement(container, j);
      typename T::value_type &right = Access<T>::getElement(container, i);
      if (compare(left, right))
      {
        std::swap(left, right);
      }
    }
  }
}

#endif
