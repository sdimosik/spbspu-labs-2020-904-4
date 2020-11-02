#include "functions.hpp"
#include <random>
#include <ctime>

void detail::fillRandom(double* array, size_t size)
{
  if (array == nullptr)
  {
    throw std::invalid_argument("Invalid argument in function fillRandom");
  }

  std::uniform_real_distribution<double> distribution(-1.0, 1.0);
  std::default_random_engine randomDevice;

  for (size_t i = 0; i < size; ++i)
  {
    array[i] = distribution(randomDevice);
  }
}
