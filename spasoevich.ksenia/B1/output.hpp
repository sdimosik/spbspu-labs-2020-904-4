#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <iostream>

template <typename T>
void print(const T& container)
{
  for (const auto& element : container)
  {
    std::cout << element << " ";
  }
  std::cout << '\n';
}

#endif
