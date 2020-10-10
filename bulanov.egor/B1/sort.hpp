#ifndef B1_SORT_HPP
#define B1_SORT_HPP

#include <functional>
#include <cstring>
#include "receiveElement.hpp"

template<typename T>
std::function<bool(T,T)> getDirection(const char* direction)
{
  if(strcmp(direction, "ascending") == 0)
  {
    return std::less<T>();
  }
  if(strcmp(direction, "descending") == 0)
  {
    return std::greater<T>();
  }
  throw std::invalid_argument("Error: unknown direction!\n");;
}

template<template<class> class Receive, class T>
void sort(T &container, Receive<T> receive, std::function<bool(const typename T::value_type, const typename T::value_type)> compare)
{
  auto last = receive.end(container);
  for(auto i = receive.begin(container); i != last; i++)
  {
    for(auto j = i; j != last; j++)
    {
      typename T::value_type &iElement = receive.element(container, i);
      typename T::value_type &jElement = receive.element(container, j);
      if(compare(jElement, iElement))
      {
        std::swap(jElement, iElement);
      }
    }
  }
}

#endif
