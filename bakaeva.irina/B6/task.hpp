#ifndef B6_TASK_HPP
#define B6_TASK_HPP

#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>
#include "functor.hpp"

void task()
{
  Functor functor;

  std::for_each(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::ref(functor));

  if ((!std::cin.eof()) && (std::cin.fail()))
  {
    throw std::invalid_argument("Error by reading data!");
  }

  functor.printInfo(std::cout);
}

#endif
