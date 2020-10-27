#ifndef FIRSTTASK_HPP
#define FIRSTTASK_HPP

#include <iostream>

#include "QueueWithPriority.hpp"
#include "commands.hpp"

void firstTask()
{
  QueueWithPriority<std::string> queue;
  std::string line;
  while(getline(std::cin, line))
  {
    if (!std::cin.good() && !std::cin.eof())
    {
      throw std::runtime_error("Error while reading in first task!\n");
    }
    std::istringstream input(line);
    interpreter(input, std::cout, queue);
  }
}

#endif
