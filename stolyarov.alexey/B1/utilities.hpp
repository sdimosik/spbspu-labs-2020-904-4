#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <vector>
#include <iostream>
#include <random>
#include <functional>

namespace utilities
{
  template <typename T>
  std::function<bool(T, T)> compareOrder(const char* sortType)
  {
    if (std::string(sortType) == "ascending")
    {
      return std::greater<const T>();
    }
    else if (std::string(sortType) == "descending")
    {
      return  std::less<const T>();
    }
    else
    {
      throw std::invalid_argument("Incorrect sort type was founded");
    }
  }

  template <template <class> class Access, class Collection>
  void bubbleSort(Collection& collection, std::function<bool(typename Collection::value_type, typename Collection::value_type)> compare)
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

  template <class Container>
  void println(const Container& collection, const char* addedLine = " ")
  {
    for (auto i = collection.begin(); i != collection.end(); ++i)
    {
      std::cout << *i << addedLine;
    }
    std::cout << "\n";
  }

  void fillRandom(double* array, int size)
  {
    if (array == nullptr)
    {
      throw std::invalid_argument("Array is null pointer");
    }
    if (size < 0)
    {
      throw std::invalid_argument("Incorrect value of size: " + std::to_string(size) + ". Should be >= 0");
    }
    std::default_random_engine generate(size);
    std::uniform_real_distribution<double> distribution(-1, 1);
    for (int i = 0; i < size; ++i)
    {
      array[i] = distribution(generate);
    }
  }
}

#endif
