#ifndef TASK_4_HPP
#define TASK_4_HPP

#include <iostream>
#include <vector>
#include "access.hpp"
#include "utilities.hpp"

void task4(const char* sortType, int size)
{
  if (size <= 0)
  {
    throw std::invalid_argument("Task4. Size should be > 0. Task 4");
  }
  std::vector<double> vector(size);
  utilities::fillRandom(vector.data(), size);
  utilities::println(vector);
  utilities::bubbleSort<IteratorAccess>(vector, utilities::compareOrder<double>(sortType));
  utilities::println(vector);
}

#endif // !TASK_4_HPP
