#include <random>
#include <string>
#include <stdexcept>
#include <iostream>
#include "access.hpp"
#include "tasks.hpp"

void task4(const std::string& order, const std::string& size)
{
  if ((order != "ascending") && (order != "descending"))
  {
    throw std::runtime_error("Invalid argument in task 4");
  }
  int vectorSize = std::stoi(size);
  if (vectorSize <= 0)
  {
    throw std::invalid_argument("Invalid vector size");
  }
  std::vector<double> array(vectorSize);
  fillRandom(array.data(), vectorSize);
  print(array, " ");
  std::function<bool(const double&, const double&)> comparator = getComparator<double>(order);
  selectionSort<IteratorAccess>(array, comparator);
  print(array, " ");
}

void fillRandom(double* array, int size)
{
  if (array == nullptr || size <= 0) 
  {
    throw std::invalid_argument("Invalid argument in function fillRandom");
  }
  std::uniform_real_distribution<double> distr(-1, 1);
  std::default_random_engine re;
  for (int i = 0; i < size; i++) {
    array[i] = distr(re);
  }
}
