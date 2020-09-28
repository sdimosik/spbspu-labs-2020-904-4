#ifndef B1_SORT_HPP
#define B1_SORT_HPP

#include <iostream>
#include <functional>
#include <cstring>
#include "type.hpp"

template<typename T>
std::function<bool(const T, const T)> get_compare(const char* direction)
{
  if(direction != nullptr)
  {
    if (std::strcmp(direction, "ascending") == 0)
    {
      return std::less<const T>();
    }
    if(std::strcmp(direction, "descending") == 0)
    {
      return std::greater<const T>();
    }
    throw std::invalid_argument("wrong direction \n");
  }
  else
  {
    throw std::invalid_argument("direction is not exist \n");
  }
}

template<template<class> class Type, class T>
void func_sort(T &collection, std::function<bool(const typename T::value_type, const typename T::value_type)> compare)
{
  using index = typename Type<T>::index;
  index begin = Type<T>::begin(collection);
  index end = Type<T>::end(collection);

  index i = begin;
  i++;
  while(i != end)
  {
    index prev_p = i;
    prev_p--;
    for (index p=i; p != begin && compare(Type<T>::get_element(collection, p), Type<T>::get_element(collection, prev_p));  p--)
    {
      std::swap(Type<T>::get_element(collection, prev_p), Type<T>::get_element(collection, p));
      if(prev_p != begin)
      {
        prev_p--;
      }
    }
    i++;
  }
}

#endif //B1_SORT_HPP
