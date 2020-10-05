#ifndef SORT_HPP
#define SORT_HPP

#include <functional>
#include <vector>
#include <string>
#include "access.hpp"

template< typename T >
std::function<bool(T, T)> getCompare(std::string orientation)
{
  if(orientation == "ascending")
  {
    return std::greater<T>();
  }
  else if(orientation == "descending")
  {
    return std::less<T>();
  }
  else
  {
    throw std::invalid_argument("Invalid sort orientation");
  }
  
}

template < template < typename > class Access, typename ContainerType>
void sort (ContainerType & data, std::function<bool(typename ContainerType::value_type, typename ContainerType::value_type)> compare)
{

  typedef Access< ContainerType > access;
  const auto begin = access::begin(data);
  const auto end = access::end(data);

  for(auto i = begin; i != end; i = access::next(i))
  {
    for(auto j = access::next(i); j != end; j = access::next(j))
    {
      if(compare(access::element(data, i), access::element(data, j)))
      {
        std::swap(access::element(data, i), access::element(data, j));
      }
    }
  }
}

#endif
