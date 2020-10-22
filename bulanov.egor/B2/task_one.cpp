#include <iostream>
#include <sstream>
#include "queueWithPriority.hpp"
#include "commands.hpp"

void task1()
{
  QueueWithPriority<std::string> queue;
  std::string line;
  while (getline(std::cin, line))
  {
    std::stringstream in(line);
    std::string command;
    in >> command;

    choiceCommand(command, queue, in, std::cout);

    if (std::cin.fail() && !std::cin.eof())
    {
      throw std::ios_base::failure("Error: there was a problem reading the data!\n");
    }
  }
}
