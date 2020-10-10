#ifndef B1_PRINTDATA_HPP
#define B1_PRINTDATA_HPP

#include <iostream>

template<class T>
void printData(const T &container, const char *separator)
{
  for (const auto &elem : container)
  {
    std::cout << elem << separator;
  }
}

#endif
