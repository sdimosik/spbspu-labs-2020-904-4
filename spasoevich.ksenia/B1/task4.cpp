#include <random>
#include <vector>
#include <ctime>
#include <stdexcept>

#include "output.hpp"
#include "sort.hpp"

void fillRandom(double* array, int size)
{
  if (array==nullptr || size<0)
{
 throw std::invalid_argument("Pointer can't be nullptr and size can't be negative\n" );
}

  std::uniform_real_distribution<> dis(-1.0, 1.0);
  std::random_device rd;  
  std::mt19937 gen(rd());

  for (int i = 0; i < size; ++i)
  { 
    array[i] = dis(gen);
  }
}

void task4(const char* direction, size_t size)
{
  if (size <= 0)
  {
    throw std::invalid_argument("Size must be more than 0.");
  }

  std::vector<double> vector(size);
  fillRandom(&vector[0], size);

  print(vector);
  selectionSort<accessUsingOperator>(vector, getDirection<double>(direction));
  print(vector);
}
