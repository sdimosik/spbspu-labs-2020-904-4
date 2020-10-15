#include "parts.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include "priority-queue.hpp"

namespace lovkacheva
{
  const char *INVALID_COMMAND = "<INVALID COMMAND>";

  void get(PriorityQueue<std::string>& queue)
  {
    if (queue.empty())
    {
      std::cout << "<EMPTY>" << '\n';
    }
    else
    {
      std::string element = queue.front();
      queue.pop();
      std::cout << element << '\n';
    }
  }

  void add(PriorityQueue<std::string>& queue, std::istringstream& in)
  {
    std::string priority;
    in >> priority;
    if (in.eof())
    {
      std::cout << INVALID_COMMAND << '\n';
      return;
    }

    std::string data;
    in >> std::ws;
    getline(in, data);
    if (data.empty())
    {
      std::cout << INVALID_COMMAND << '\n';
      return;
    }

    if (priority == "high")
    {
      queue.put(data, PriorityQueue<std::string>::ElementPriority::HIGH);
    }
    else if (priority == "normal")
    {
      queue.put(data, PriorityQueue<std::string>::ElementPriority::NORMAL);
    }
    else if (priority == "low")
    {
      queue.put(data, PriorityQueue<std::string>::ElementPriority::LOW);
    }
    else
    {
      std::cout << INVALID_COMMAND << '\n';
    }
  };

  void processCommand(PriorityQueue<std::string>& queue, const std::string& command)
  {
    std::istringstream in(command);
    std::string commandType;
    in >> commandType;
    if (in.fail())
    {
      if (in.eof())
      {
        std::cout << INVALID_COMMAND << '\n';
      }
      else
      {
        throw std::runtime_error("Invalid input");
      }
    }

    if (commandType == "get")
    {
      in >> std::ws;
      if (in.peek() != EOF)
      {
        std::cout << INVALID_COMMAND << '\n';
      }
      get(queue);
    }
    else if (commandType == "accelerate")
    {
      in >> std::ws;
      if (in.peek() != EOF)
      {
        std::cout << INVALID_COMMAND << '\n';
      }
      queue.accelerate();
    }
    else if (commandType == "add")
    {
      add(queue, in);
    }
    else
    {
      std::cout << INVALID_COMMAND << '\n';
    }
  }
}

void lovkacheva::partOne()
{
  PriorityQueue<std::string> queue;
  std::string command;
  getline(std::cin, command);
  while (std::cin)
  {
    processCommand(queue, command);
    getline(std::cin, command);
  }
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Invalid input");
  }
}
