#ifndef B6_TASK_HPP
#define B6_TASK_HPP

#include <iostream>
#include <iterator>
#include <functional>
#include <algorithm>
#include "functor.hpp"

namespace task
{
  void exec();
  
  void exec()
  {
    Functor functor = std::for_each(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), Functor());;
    
    if ((!std::cin.eof()) && (std::cin.fail()))
    {
      throw std::invalid_argument("Fail while reading");
    }
    
    functor.print(std::cout);
  }
}
#endif //B6_TASK_HPP
