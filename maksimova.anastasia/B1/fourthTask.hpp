#ifndef FOURTHTASK_HPP
#define FOURTHTASK_HPP

#include <stdexcept>
#include <random>
#include <ctime>

#include "print.hpp"
#include "access.hpp"
#include "sort.hpp"

void fillRandom(double * array, int size)
{
  std::default_random_engine generator(time(0));
  std::uniform_real_distribution<double> distr(-1, 1);
  for (int i = 0; i < size; ++i)
  {
    array[i] = distr(generator);
  }
}

void fourthTask (const std::string& type, const size_t size)
{
  if(size <= 0)
  {
    throw std::invalid_argument("Wrong size!\n");
  }
  std::function<bool(double, double)> compare = get_compare<double>(type.c_str());
  std::vector<double> randVector(size);
  fillRandom(randVector.data(), size);
  print(randVector);
  sort<at_access>(randVector, compare);
  print(randVector);
}

#endif
