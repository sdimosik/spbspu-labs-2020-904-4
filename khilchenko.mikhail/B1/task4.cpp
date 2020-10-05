#include <vector>
#include <cstdlib>
#include <random>
#include "access.hpp"
#include "sort.hpp"
#include "print.hpp"

void fillRandom(double* array, int size)
{
  if(size <= 0)
  {
    throw std::invalid_argument("Invalid size of array in task4");
  }
  if(array == nullptr)
  {
    throw std::invalid_argument("Invalid array pointer in task4");
  }
  std::default_random_engine gen;
  std::uniform_real_distribution<double> distribution(-1.0, 1.0);
  for(int i = 0; i < size; i++)
  {
    array[i] = distribution(gen);
  }
}

void task4(char* order, size_t size)
{
  std::vector<double> vector(size);

  fillRandom(vector.data(), size);

  for(auto i = vector.begin(); i < vector.end(); i++)
  {
    std::cout << *i << " ";
  }
  std::cout << '\n';

  std::function<bool(double, double)> compare = getCompare<double>(order);
  sort<IndexAccess>(vector, compare);
  print(vector);
}
