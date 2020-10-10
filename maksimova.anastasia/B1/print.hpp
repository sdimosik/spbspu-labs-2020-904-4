#ifndef PRINT_HPP
#define PRINT_HPP

#include <iostream>

template <class T>
void print(T &container)
{
  for(const auto &item : container)
  {
    std::cout << item << " ";
  }
  std::cout << '\n';
}

#endif
