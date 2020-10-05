#ifndef B1_UTILS_HPP
#define B1_UTILS_HPP

#include <vector>
#include <iostream>
#include <random>
#include <functional>

namespace utils
{
  //declaration
  
  enum class ArgSort;
  
  ArgSort getArgSort(const char *sortType);
  
  template<typename T>
  std::function<bool(T, T)> compareOrder(ArgSort argSort);
  
  template<template<class> class Access, class Collection>
  void bubbleSort(Collection &collection, std::function<bool(typename Collection::value_type, typename Collection::value_type)> compare);
  
  void fillRandom(double *array, int size);
  
  //definition
  
  enum class ArgSort
  {
    ascending,
    descending
  };
  
  ArgSort getArgSort(const char *sortType)
  {
    if (std::string(sortType) == "descending")
    {
      return ArgSort::descending;
    }
    else
    {
      return ArgSort::ascending;
    }
  }
  
  template<typename T>
  std::function<bool(T, T)> compareOrder(ArgSort argSort)
  {
    if (argSort == ArgSort::ascending)
    {
      return std::greater<const T>();
    }
    else if (argSort == ArgSort::descending)
    {
      return std::less<const T>();
    }
    else
    {
      throw std::invalid_argument("Invalid sort type!");
    }
  }
  
  template<template<class> class Access, class Collection>
  void bubbleSort(Collection &collection, std::function<bool(typename Collection::value_type, typename Collection::value_type)> compare)
  {
    auto begin = Access<Collection>::begin(collection);
    auto end = Access<Collection>::end(collection);
    for (auto i = begin; i != end; ++i)
    {
      for (auto j = i; j != end; ++j)
      {
        if (compare(Access<Collection>::getElement(collection, i), Access<Collection>::getElement(collection, j)))
        {
          std::swap(Access<Collection>::getElement(collection, i), Access<Collection>::getElement(collection, j));
        }
      }
    }
  }
  
  template<class container>
  void println(const container &collection, const char *addedLine = " ")
  {
    for (auto i = collection.begin(); i != collection.end(); ++i)
    {
      std::cout << *i << addedLine;
    }
    std::cout << "\n";
  }
  
  void fillRandom(double *array, int size)
  {
    if (array == nullptr || size <= 0)
    {
      throw std::invalid_argument("fillRandom: array is nullptr or size 0");
    }
    std::default_random_engine generate;
    std::uniform_real_distribution<double> distrib(-1, 1);
    for (int i = 0; i < size; i++)
    {
      array[i] = distrib(generate);
    }
  }
}

#endif //B1_UTILS_HPP
