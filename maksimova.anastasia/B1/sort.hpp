#ifndef SORT_HPP
#define SORT_HPP

#include <algorithm>
#include <functional>
#include <cstring>

template<typename T>
std::function<bool(const T, const T)> get_compare(const char* direction)
{
  if(!direction)
  {
    throw std::invalid_argument("Direction is not exist!\n");
  }
  else if(std::strcmp(direction, "ascending") == 0)
  {
    return std::less<const T>();
  }
  else if (std::strcmp(direction, "descending") == 0)
  {
    return std::greater<const T>();
  }
  throw std::invalid_argument("Wrong direction!\n");
}


template <template <typename> class AccessType, typename ContainerType>
void sort(ContainerType& container,
          std::function<bool(const typename ContainerType::value_type, const typename ContainerType::value_type)> compare)
{
  auto begin = AccessType<ContainerType>::begin(container);
  auto end = AccessType<ContainerType>::end(container);
  for (auto i = begin; i != end; ++i)
  {
    auto temp = i;
    for(auto j = i; j != end; ++j)
    {
      if(compare(AccessType<ContainerType>::get_element(container, j),
          AccessType<ContainerType>::get_element(container, temp)))
      {
        temp = j;
      }
    }
    std::swap(AccessType<ContainerType>::get_element(container,i), AccessType<ContainerType>::get_element(container,temp));
  }
}

#endif
