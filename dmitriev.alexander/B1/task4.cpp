#include <iostream>
#include <vector>
#include <random>
#include "extensions.hpp"
#include "sort.hpp"

void fillRandom(double *array, int size)
{
  std::random_device random_device;
  std::mt19937 random_engine(random_device());
  std::uniform_real_distribution<double> dist(-1.0, 1.0);

  for (int i = 0; i < size; i++)
  {
    array[i] = dist(random_engine);
  }
}

void task4(const char *typeString, const int size)
{
  if (size <= 0)
  {
    throw std::invalid_argument("Size must be positive!\n");
  }

  std::function<bool(double, double)> compare = getComparisonType<double>(typeString);

  std::vector<double> vector(size);
  fillRandom(vector.data(), size);
  printArray(vector);
  std::cout << std::endl;

  sort<AccessByBrackets>(vector, compare);
  printArray(vector);
}
