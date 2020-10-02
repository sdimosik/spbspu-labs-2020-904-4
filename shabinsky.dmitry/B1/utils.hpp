#ifndef B1_UTILS_HPP
#define B1_UTILS_HPP

#include <vector>
#include <iostream>
#include <random>

namespace utils
{
  //declaration
  
  enum class ArgSort;
  
  ArgSort getArgSort(const char *sortType);
  
  template<template<class> class Access, class Collection>
  void bubbleSort(Collection &collection, ArgSort argSort);
  
  template<class container>
  void print(const container &collection);
  
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
  
  template<template<class> class Access, class Collection>
  void bubbleSort(Collection &collection, ArgSort argSort)
  {
    auto begin = Access<Collection>::begin(collection);
    auto end = Access<Collection>::end(collection);
    for (auto i = begin; i != end; ++i)
    {
      for (auto j = i; j != end; ++j)
      {
        if (argSort == ArgSort::ascending &&
          Access<Collection>::getElement(collection, i) > Access<Collection>::getElement(collection, j))
        {
          std::swap(Access<Collection>::getElement(collection, i), Access<Collection>::getElement(collection, j));
        }
        else if (argSort == ArgSort::descending &&
          Access<Collection>::getElement(collection, i) < Access<Collection>::getElement(collection, j))
        {
          std::swap(Access<Collection>::getElement(collection, i), Access<Collection>::getElement(collection, j));
        }
      }
    }
  }
  
  template<class container>
  void print(const container &collection)
  {
    for (auto i = collection.begin(); i != collection.end(); ++i)
    {
      std::cout << *i << " ";
    }
    std::cout << "\n";
  }
  
  void fillRandom(double *array, int size)
  {
    std::default_random_engine generate;
    std::uniform_real_distribution<double> distrib(-1, 1);
    for (int i = 0; i < size; i++)
    {
      array[i] = distrib(generate);
    }
  }
}

#endif //B1_UTILS_HPP
