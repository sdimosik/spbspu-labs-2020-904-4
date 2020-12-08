#ifndef SPBSPU_LABS_2020_904_4_PRINT_HPP
#define SPBSPU_LABS_2020_904_4_PRINT_HPP

#include <iostream>

template<class T>
void print(const T &container, const char *delimiter)
{
  for (const auto &elem : container)
  {
    std::cout << elem << delimiter;
  }
}

#endif
