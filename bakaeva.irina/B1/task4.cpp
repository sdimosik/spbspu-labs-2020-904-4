#include <vector>
#include <cstdlib>
#include <random>
#include "sort.hpp"
#include "printData.hpp"

void fillRandom(double *array, int size)
{
  if (array == nullptr)
  {
    throw std::invalid_argument("Pointer must be not nullptr!\n");
  }

  if (size <= 0)
  {
    throw std::invalid_argument("Size of array must be positive!\n");
  }

  std::uniform_real_distribution<double> distr(-1, 1);
  std::default_random_engine re;
  for (int i = 0; i < size; i++)
  {
    array[i] = distr(re);
  }
}

void task4(const char *orientation, const int size)
{
  if (size <= 0)
  {
    throw std::invalid_argument("Size must be greater than zero!\n");
  }

  std::vector<double> vector(size);
  fillRandom(vector.data(), size);

  printData(vector, " ");
  std::cout << '\n';
  std::function<bool(double, double)> compare = getComparisonSign<double>(orientation);
  sort<AccessByBrackets>(vector, compare);
  printData(vector, " ");
}
