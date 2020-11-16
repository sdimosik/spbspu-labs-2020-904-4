#include "tasks.hpp"
#include <stdexcept>
#include <iostream>
#include "priority-queue.hpp"
#include "functions.hpp"

void task::doFirstTask()
{
  detail::QueueWithPriority<std::string> queue;
  std::string string;
  while (std::getline(std::cin, string))
  {
    std::stringstream stringStream(string);
    std::string command;
    stringStream >> command;
    detail::parseCommand(command, queue, stringStream, std::cout);
  }

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::runtime_error("Error by reading data!\n");
  }
}
