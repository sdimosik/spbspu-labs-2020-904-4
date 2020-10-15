#include <iostream>
#include <sstream>
#include <string>
#include "queue-with-priority.hpp"

template <typename T>
void add(std::istringstream& input, std::ostream& output, QueueWithPriority<T>& queueWithPriority)
{
  std::string priority;
  std::string data;
  input >> priority;
  if (priority.empty())
  {
    output << "<INVALID COMMAND>\n";
    return;
  }
  input >> data;
  if (!input.eof()) 
  {
    std::string temp;
    std::getline(input, temp);
    data += temp;
  }
  if (data.empty())
  {
    output << "<INVALID COMMAND>\n";
    return;
  }
  if (priority == "high")
  {
    queueWithPriority.add(QueueWithPriority<std::string>::ElementPriority::HIGH, data);
  }
  else if (priority == "normal")
  {
    queueWithPriority.add(QueueWithPriority<std::string>::ElementPriority::NORMAL, data);
  }
  else if (priority == "low")
  {
    queueWithPriority.add(QueueWithPriority<std::string>::ElementPriority::LOW, data);
  }
  else
  {
    output << "<INVALID COMMAND>\n";
    return;
  }
}

template <typename T>
void get(std::ostream& output, QueueWithPriority<T>& queueWithPriority)
{
  if (queueWithPriority.isEmpty())
  {
    output << "<EMPTY>\n";
  }
  else
  {
    output << queueWithPriority.get() << '\n';
    queueWithPriority.pop();
  }
}

template <typename T>
void accelerate(QueueWithPriority<T>& queueWithPriority)
{
  queueWithPriority.accelerate();
}

void task1()
{
  QueueWithPriority<std::string> queueWithPriority;
  std::string current;
  while (std::getline(std::cin, current))
  {
    std::istringstream input(current);
    std::string command;
    input >> command;
    if (command == "add")
    {
      add(input, std::cout, queueWithPriority);
    }
    else if (command == "get")
    {
      get(std::cout, queueWithPriority);
    }
    else if (command == "accelerate")
    {
      accelerate(queueWithPriority);
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
      continue;
    }
  }
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error while reading in task 1");
  }
}
