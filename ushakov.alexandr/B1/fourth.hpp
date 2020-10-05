#ifndef FOURTH_HPP
#define FOURTH_HPP

#include <stdexcept>
#include <vector>
#include <random>
#include "print.hpp"
#include "sort.hpp"
#include "detail.hpp"
#include "indexAccess.hpp"

void fillRandom(double *array, long size)
{
  if (!array)
  {
    throw std::invalid_argument("Invalid argument in fillRandom function: null array pointer");
  }

  if (size < 0)
  {
    throw std::invalid_argument(
        "Invalid argument in fillRandom function: invalid array size (" + std::to_string(size) + ")");
  }

  std::default_random_engine re(size);
  std::uniform_real_distribution<double> distr(-1, 1);

  for (long i = 0; i < size; ++i)
  {
    array[i] = distr(re);
  }
}

void fourthTask(const char *sortingType, size_t size)
{
  std::vector<double> vector(size);

  fillRandom(vector.data(), size);

  print(vector);

  collectionSort<IndexAccess>(vector, detail::getCompare<double>(sortingType));

  print(vector);
}

#endif
