#ifndef LABS_FUNCTIONS_HPP
#define LABS_FUNCTIONS_HPP
#include <iostream>
#include <cstring>
#include <functional>
#include "accesses.hpp"

namespace detail
{
  template<typename T>
  std::function<bool(const T, const T)> getCompare(const char* sortDirection)
  {
    if (std::strcmp(sortDirection, "ascending") == 0)
    {
      return std::less<const T>();
    }
    if (std::strcmp(sortDirection, "descending") == 0)
    {
      return std::greater<const T>();
    }
    throw std::invalid_argument("Invalid sort\n");
  }

  template<template<class> class Access, class Container>
  void sortContainer(Container& data, std::function<bool(typename Container::value_type, typename Container::value_type)> compare)
  {
    auto begin = Access<Container>::getBegin(data);
    auto end = Access<Container>::getEnd(data);
    while (begin != end)
    {
      auto j = begin;
      while (j != end)
      {
        typename Container::value_type& left = Access<Container>::getElement(data, j);
        typename Container::value_type& right = Access<Container>::getElement(data, begin);
        if (compare(left, right))
        {
          std::swap(left, right);
        }
        j++;
      }
      begin++;
    }
  }

  template<typename Container>
  void printContainer(const Container& container)
  {
    for (const auto& element : container)
    {
      std::cout << element << " ";
    }
    std::cout << '\n';
  }
  void fillRandom(double* array, size_t size);
}
#endif
