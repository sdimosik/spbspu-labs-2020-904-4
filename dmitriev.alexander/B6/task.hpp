#ifndef TASK_HPP
#define TASK_HPP

#include <functional>
#include <algorithm>
#include <iterator>
#include "functor.hpp"

void task()
{
  Functor functor = std::for_each(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), Functor());

  if ((!std::cin.eof()) && (std::cin.fail()))
  {
    throw std::ios_base::failure("Fail while reading data!");
  }

  std::cout << functor;

}

#endif
