#ifndef B8_TASK_HPP
#define B8_TASK_HPP

#include <iostream>
#include "text.hpp"

namespace task
{
  void exec(size_t lineWidth);
  
  void exec(size_t lineWidth)
  {
    Text textHandler;
    textHandler.read(std::cin);
    textHandler.print(std::cout, lineWidth);
  }
}

#endif //B8_TASK_HPP
