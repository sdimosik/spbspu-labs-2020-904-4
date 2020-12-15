#ifndef B8_TASK_HPP
#define B8_TASK_HPP

#include <iterator>
#include <functional>
#include <algorithm>
#include "stateMachine.hpp"
#include "iteratorInput.hpp"

namespace task
{
  void exec(size_t lineWidth);
  
  void exec(size_t lineWidth)
  {
    StateMachine stateMachine(std::cout, lineWidth);
    std::for_each(IteratorInput(std::cin), IteratorInput(), std::ref(stateMachine));
    
    if ((!std::cin.eof()) && (std::cin.fail()))
    {
      throw std::invalid_argument("Fail while reading");
    }
  }
}

#endif //B8_TASK_HPP
