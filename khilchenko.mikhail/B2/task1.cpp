#include <iostream>
#include <string>

#include "queueWithPriority.hpp"

void add(QueueWithPriority<std::string>& queue)
{
  std::string priority;
  std::string data;
  std::string restPartOfInput;
  std::cin >> priority;
  std::cin >> data;
  std::getline(std::cin, restPartOfInput);
  data += restPartOfInput;

  if(priority.empty() || data.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
  }

  if(priority == "low")
  {
    queue.putElementToQueue(data, queue.LOW);
  }
  else if(priority == "normal")
  {
    queue.putElementToQueue(data, queue.NORMAL);
  }
  else if(priority == "high")
  {
    queue.putElementToQueue(data, queue.HIGH);
  }
  else
  {
    std::cout << "<INVALID COMMAND>\n";
  }
}

void get(QueueWithPriority<std::string>& queue)
{
  if(!queue.isEmpty())
  {
    std::cout << queue.getFirstElement() << '\n';
    queue.removeFirstElement();
  }
  else
  {
    std::cout << "<EMPTY>\n";
  }
}

void accelerate(QueueWithPriority<std::string>& queue)
{
  queue.accelerate();
}

void task1()
{
  QueueWithPriority<std::string> queue;
  while(!std::cin.eof() && std::cin.good())
  {
    std::string operation;
    std::cin >> operation;

    if(operation == "add")
    {
      add(queue);
    }
    else if(operation == "get")
    {
      get(queue);
    }
    else if(operation == "accelerate")
    {
      accelerate(queue);
    }
    else if(operation != "")
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }

  if(std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error of reading data in task 1");
  }
}
