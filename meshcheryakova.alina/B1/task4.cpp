#include <ctime>
#include <random>
#include <vector>
#include "print.cpp"
#include "sort.hpp"
void fillRandom(double* array, int size);
void task_4(const char* direction, int size)
{
  std::function<bool(double, double)> compare = get_compare<double>(direction);
  if(size <= 0)
  {
      throw std::invalid_argument("size of array must be positive ! \n");
  }

  std::vector<double> array(size);
  fillRandom(array.data(),size);
  print(array);
  func_sort<type_iter>(array, compare);
  print(array);

};

void fillRandom(double* array, int size)
{
  std::default_random_engine generator(time(0));
  std::uniform_real_distribution<double> distribution(-1, 1);
  for (int i = 0; i < size; i++)
  {
    array[i] = distribution(generator);
  }
}
