#ifndef PRINT_HPP
#define PRINT_HPP

#include <iostream>

template< typename T >
void print(const T& container)
{
  for(auto i = container.begin(); i != container.end(); i++)
  {
    std::cout << *i << " ";
  }
  std::cout << '\n';
}

#endif
