#include <vector>
#include <random>
#include "print.hpp"
#include "sort.hpp"


void fillRandom(double *array, int size)
{
  if (array == nullptr)
  {
    throw std::invalid_argument("Error: pointer can not be nullptr!\n");
  }

  if (size <= 0)
  {
    throw std::invalid_argument("Error: size of array should be positive!\n");
  }

  std::uniform_real_distribution<double> distribution(-1, 1);
  std::default_random_engine gen(time(0));
  for (int i = 0; i < size; i++)
  {
    array[i] = distribution(gen);
  }
}

void task4(const char *direction, const int size)
{
  if (size <= 0)
  {
    throw std::invalid_argument("Error: size cannot be less then zero!\n");
  }

  std::vector<double> vector(size);
  fillRandom(vector.data(), size);
  print(vector);
  std::cout << '\n';

  std::function<bool(double, double)> compare = getDirection<double>(direction);
  sort(vector, IndexReceive<std::vector<double>>(), compare);
  print(vector);
}
