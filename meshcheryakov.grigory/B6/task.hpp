#ifndef SPBSPU_LABS_2020_904_4_TASK_HPP
#define SPBSPU_LABS_2020_904_4_TASK_HPP

#include <iostream>
#include <iterator>
#include <functional>
#include <algorithm>
#include "functor.hpp"

void task()
{
  Functor functor;

  std::for_each(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::ref(functor));

  if ((!std::cin.eof()) && (std::cin.fail()))
  {
    throw std::invalid_argument("Fail while reading!\n");
  }

  functor.print(std::cout);
}

#endif
