#include <iostream>
#include <iterator>
#include <algorithm>
#include "functor.hpp"

void task_1()
{
  Functor functor = std::for_each((std::istream_iterator<int>(std::cin)), std::istream_iterator<int>(), Functor());

  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::ios_base::failure(" fail in reading stream ! \n");
  }

  std::cout << functor;
}
