#ifndef B1_TASK4_HPP
#define B1_TASK4_HPP

#include <iostream>
#include <vector>
#include "access.hpp"
#include "utils.hpp"

namespace task4
{
  void exec(const char *sortType, int size);
  
  void exec(const char *sortType, int size)
  {
    if (size <= 0)
    {
      throw std::invalid_argument("Task4. Size should be > 0");
    }
    std::vector<double> vector(size);
    utils::fillRandom(vector.data(), size);
    utils::print(vector);
    utils::bubbleSort<IteratorAccess>(vector, utils::getArgSort(sortType));
    utils::print(vector);
  }
}

#endif //B1_TASK4_HPP
