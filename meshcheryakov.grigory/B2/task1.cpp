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
      throw std::ios_base::failure("Error of reading data");
    }

    std::stringstream input(line);
    std::string command;
    input >> command;

    if (command == "add")
    {
      add(queue, input, std::cout);
    }
    else if (command == "get")
    {
      get(queue, std::cout);
    }
    else if (command == "accelerate")
    {
      accelerate(queue);
    }
    else
    {
      std::cout << "<INVALID COMMAND>" << "\n";
    }
  }

}
