#include <iostream>
#include <sstream>
#include "queueWithPriority.hpp"
#include "parseCommand.hpp"

void task1()
{
  QueueWithPriority<std::string> queue;
  std::string string;
  while (std::getline(std::cin, string))
  {
    std::stringstream stringStream(string);
    std::string command;
    stringStream >> command;
    parseCommand(command, queue, stringStream, std::cout);
  }

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::runtime_error("Error by reading data!\n");
  }
}
