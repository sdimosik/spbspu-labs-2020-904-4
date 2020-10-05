#ifndef TASK4
#define TASK4
#include <random>
#include <stdexcept>
#include <vector>
#include "sort.hpp"
#include "print.hpp"

void fillRandom(double* array, int size)
{
  if (array == nullptr)
  {
    throw std::invalid_argument("Empty array");
  }
  if (size <= 0)
  {
    throw std::invalid_argument("Size must be natural");
  }
  std::default_random_engine gen;
  std::uniform_real_distribution<double> distrib(-1, 1);
  for (int i = 0; i < size; i++)
  {
    array[i] = distrib(gen);
  }
}

void task4(const char* parametr, int size)
{
  if (!isDirectionStringCorrect(parametr))
  {
    throw std::invalid_argument("Invalid sort direction in task 4");
  }
  Direction direction = (strcmp(parametr, "ascending") == 0 ? Direction::ascending : Direction::descending);

  if (size <= 0)
  {
    throw std::invalid_argument("Size must be natural");
  }

  std::vector<double> vector(size);

  fillRandom(vector.data(), size);
  print(vector, " ");

  bubbleSort<IteratorAccess>(vector, direction);
  print(vector, " ");
}
#endif // !TASK4
