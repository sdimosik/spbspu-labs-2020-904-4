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
    if (!std::cin.good() && !std::cin.eof())
    {
      throw std::ios_base::failure("Task 1: Reading data failure");
    }

    std::stringstream input(line);
    std::string command;
    input >> command;

    if (command == "add")
    {
      commands::add(queue, input, std::cout);
    }
    else if (command == "get")
    {
      commands::get(queue, std::cout);
    }
    else if (command == "accelerate")
    {
      commands::accelerate(queue);
    }
    else
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
  }
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Task 1: Reading data failure");
  }
}
