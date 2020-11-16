#ifndef B3_TASK2_HPP
#define B3_TASK2_HPP

#include <algorithm>
#include <iostream>
#include "factorial.hpp"

namespace task2
{
  void exec();
  
  void exec()
  {
    std::copy(Factorial::begin(), Factorial::end(), std::ostream_iterator<size_t>(std::cout, " "));
    std::cout << '\n';
    
    std::reverse_copy(Factorial::begin(), Factorial::end(), std::ostream_iterator<size_t>(std::cout, " "));
    std::cout << '\n';
  }
}

#endif //B3_TASK2_HPP
