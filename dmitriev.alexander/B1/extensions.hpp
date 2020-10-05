#ifndef EXTENSIONS_HPP
#define EXTENSIONS_HPP

#include <iostream>
#include <map>
#include <vector>
#include "sort.hpp"

template<class T>
void printArray(const T &array, const char *delimiter = " ")
{
  for (const auto &elem : array)
  {
    std::cout << elem << delimiter;
  }
}

template<typename T>
std::function<bool(const T, const T)> getComparisonType(const char *typeString)
{
  if (typeString != nullptr)
  {
    if (std::strcmp(typeString, "ascending") == 0)
    {
      return std::less<const T>();
    }
    if (std::strcmp(typeString, "descending") == 0)
    {
      return std::greater<const T>();
    }
    throw std::invalid_argument("Unknown operator!\n");
  }

  throw std::invalid_argument("Nullptr given!\n");
}

#endif
