#include<string>
#include<iostream>
#include<sstream>
#include"priority-queue.hpp"

template <typename T>
void add(std::istringstream& input, std::ostream& output, priorityQueue<T>& queue)
{
  std::string priority;
  std::string data;
  input >> priority;
  if (priority.empty())
  {
    output << "<INVALID COMMAND>" << '\n';
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
    output << "<INVALID COMMAND>" << '\n';
    return;
  }
  if (priority == "high")
  {
    queue.addElementToQueue(data, priorityQueue<std::string>::ElementPriority::HIGH);
  }
  else if (priority == "normal")
  {
    queue.addElementToQueue(data, priorityQueue<std::string>::ElementPriority::NORMAL);
  }
  else if (priority == "low")
  {
    queue.addElementToQueue(data, priorityQueue<std::string>::ElementPriority::LOW);
  }
  else
  {
    output << "<INVALID COMMAND>" << '\n';
    return;
  }
}

template <typename T>
void get(std::ostream& output, priorityQueue<T>& queue)
{
  if (queue.isEmpty())
  {
    output << "<EMPTY>" << '\n';
  }
  else
  {
    output << queue.getElementFromQueue() << '\n';
    queue.deleteElementFromQueue();
  }
}

template <typename T>
void accelerate(priorityQueue<T>& queue)
{
  queue.accelerate();
}

void task1()
{
  priorityQueue<std::string> queue;
  std::string commandLine;

  while (std::getline(std::cin, commandLine))
  {
    if (!commandLine.empty())
    {
      std::istringstream streamLine(commandLine);
      std::string command;
      streamLine >> command;

      if (command == "get")
      {
        get(std::cout, queue);
      }

      else if (command == "accelerate")
      {
        accelerate(queue);
      }

      else if (command == "add")
      {
        add(streamLine, std::cout, queue);
      }

      else
      {
        std::cout << "<INVALID COMMAND>" << '\n';
        continue;
      }
    }
  }
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error in reading Task1");
  }

}

