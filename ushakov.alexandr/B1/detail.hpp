#ifndef DETAIL_HPP
#define DETAIL_HPP

#include <functional>
#include <cstring>

namespace detail
{
  template<typename T>
  std::function<bool(T, T)> getCompare(const char *sortingType)
  {
    if (strcmp(sortingType, "ascending") == 0)
    {
      return std::less<const T>();
    }
    else if (strcmp(sortingType, "descending") == 0)
    {
      return std::greater<const T>();
    }
    else
    {
      throw std::invalid_argument("Invalid sort type!");
    }
  }
}

#endif
