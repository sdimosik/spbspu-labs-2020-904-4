#ifndef B1_PRINT_HPP
#define B1_PRINT_HPP

#include <iostream>
#include <iterator>


template<class T>
void print(const T &container, bool isNeedSpace = true)
{
  for (typename T::const_iterator temp = container.begin(); temp != container.end(); temp++)
  {
    std::cout << *temp;
    if (isNeedSpace)
    {
      std::cout << " ";
    }
  }
}

#endif
