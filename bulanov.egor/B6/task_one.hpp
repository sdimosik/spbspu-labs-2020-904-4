#ifndef B6_TASK_ONE_HPP
#define B6_TASK_ONE_HPP

#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>

#include "functor.hpp"

void task1()
{
  Functor functor = std::for_each(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), Functor());

  if ((!std::cin.eof()) && (std::cin.fail()))
  {
    throw std::invalid_argument("Error: there was a problem reading the data!\n");
  }

  functor.printInfo(std::cout);
}

#endif
