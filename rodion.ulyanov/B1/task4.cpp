#include <vector>
#include <cstdlib>
#include <random>
#include "sort.hpp"
#include "print.hpp"

void fillRandom(double *array, int size)
{
  if (array == nullptr)
  {
    throw std::invalid_argument("Array pointer cannot be nullptr");
  }

  if (size <= 0)
  {
    throw std::invalid_argument("Size of array cannot be negative");
  }

  std::uniform_real_distribution<double> distribution(-1, 1);
  std::default_random_engine gen;
  for (int i = 0; i < size; i++)
  {
    array[i] = distribution(gen);
  }
}

void task4(const char *direction, const int size)
{
  if (size <= 0)
  {
    throw std::invalid_argument("Array size must must be bigger than zero!\n");
  }

  std::vector<double> vector(size);
  fillRandom(vector.data(), size);
  print(vector, " ");
  std::cout << '\n';
  std::function<bool(double, double)> compare = getCompare<double>(direction);
  sort<IndexAccess>(vector, compare);
  print(vector, " ");
}
