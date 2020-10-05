#include "parts.hpp"
#include <iostream>
#include <random>
#include <chrono>
#include "access.hpp"
#include "detail.hpp"
#include "bubble-sort.hpp"
#include "print-contents.hpp"
namespace lovkacheva
{
  void fillRandom(double * array, int size)
  {
    if (array == nullptr)
    {
      throw std::invalid_argument("The array must not be nullptr");
    }
    if (size < 0)
    {
      throw std::invalid_argument("The array size must not be negative, size = " + std::to_string(size) + " is.");
    }
    const double lowerBound = -1.0;
    const double upperBound = 1.0;
    std::uniform_real_distribution<double> distribution(lowerBound, upperBound);

    std::default_random_engine engine(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    for (int i = 1; i < size; ++i)
    {
      array[i] = distribution(engine);
    }
  }
}

void lovkacheva::partFour(std::string order, int vectorSize)
{
  std::vector<double> vector(vectorSize);
  if (vector.empty())
  {
    return;
  }
  lovkacheva::fillRandom(&vector[0], vectorSize);
  std::function<bool(double, double)> compare = detail::getCompare<double>(order);
  printContents(vector);
  bubbleSort<std::vector<double>, IndexOperatorAccess<std::vector<double>>>(vector, compare);
  printContents(vector);
}
