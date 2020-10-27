#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include"queueWithPriority.hpp"

void add(std::istringstream& input, QueueWithPriority<std::string>& queueWithPriority)
{
  std::string priority;
  input >> priority;
  if (priority.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  std::string data;
  input >> data;
  if (!input.eof())
  {
    std::string additionalData;
    getline(input, additionalData);
    data += additionalData;
  }
  if (data.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  if (priority == "high")
  {
    queueWithPriority.putElementToQueue(data, QueueWithPriority<std::string>::ElementPriority::HIGH);
  }
  else if (priority == "normal")
  {
    queueWithPriority.putElementToQueue(data, QueueWithPriority<std::string>::ElementPriority::NORMAL);
  }
  else if (priority == "low")
  {
    queueWithPriority.putElementToQueue(data, QueueWithPriority<std::string>::ElementPriority::LOW);
  }
  else
  {
    std::cout << "<INVALID COMMAND>\n";
  }
}

void task1()
{
  QueueWithPriority<std::string> queueWithPriority;
  std::string fullString;
  while (std::getline(std::cin, fullString))
  {
    std::istringstream input(fullString);
    std::string command;
    input >> command;
    if (command == "add")
    {
      add(input, queueWithPriority);
    }

    else if (command == "get")
    {
      if (!queueWithPriority.empty())
      {
        std::cout << queueWithPriority.getElementFromQueue() << '\n';
        queueWithPriority.removeElementFromQueue();
      }
      else
      {
        std::cout << "<EMPTY>\n";
      }
    }

    else if (command == "accelerate")
    {
      queueWithPriority.accelerate();
    }

    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }

  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error while reading task 1");
  }
}
