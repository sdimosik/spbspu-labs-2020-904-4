#include <iostream>
#include <stdexcept>
#include <sstream>
#include "queueWithPriority.hpp"

const std::string INVALID_COMMAND = "<INVALID COMMAND>";
const std::string EMPTY_LIST = "<EMPTY>";

void addCommand(QueueWithPriority<std::string> &queue, std::stringstream &sin, std::ostream &ostream)
{
  std::string priorityString;
  sin >> std::ws;
  sin >> priorityString;
  sin >> std::ws;
  std::string data;
  std::getline(sin, data, '\0');
  if (data.empty())
  {
    ostream << INVALID_COMMAND << std::endl;
    return;
  }
  if (priorityString == "low")
  {
    queue.putElementToQueue(data, QueueWithPriority<std::string>::ElementPriority::LOW_PRIORITY);
  } else if (priorityString == "normal")
  {
    queue.putElementToQueue(data, QueueWithPriority<std::string>::ElementPriority::NORMAL_PRIORITY);
  } else if (priorityString == "high")
  {
    queue.putElementToQueue(data, QueueWithPriority<std::string>::ElementPriority::HIGH_PRIORITY);
  } else
  {
    ostream << INVALID_COMMAND << std::endl;
  }
}

void getCommand(QueueWithPriority<std::string> &queue, std::ostream &ostream)
{
  if (queue.isEmpty())
  {
    ostream << EMPTY_LIST << std::endl;
    return;
  }

  std::string element;
  queue.getElementFromQueue(element);
  ostream << element << std::endl;
}

void accelerateCommand(QueueWithPriority<std::string> &queue, std::stringstream &sin, std::ostream &ostream)
{
  if (!sin.eof())
  {
    ostream << INVALID_COMMAND << std::endl;
    return;
  }
  queue.accelerate();
}

void parseCommand(QueueWithPriority<std::string> &queue, std::string &input, std::ostream &ostream)
{
  std::stringstream sin(input);
  std::string command;
  sin >> command;
  if (command == "add")
  {
    addCommand(queue, sin, ostream);
  } else if (command == "get")
  {
    getCommand(queue, ostream);
  } else if (command == "accelerate")
  {
    accelerateCommand(queue, sin, ostream);
  } else
  {
    ostream << INVALID_COMMAND << std::endl;
  }
}

void task1()
{
  QueueWithPriority<std::string> queue;
  std::string input;
  while (getline(std::cin, input))
  {
    if (!std::cin.good() && !std::cin.eof())
    {
      throw std::ios_base::failure("Error while reading occurred!\n");
    }
    parseCommand(queue, input, std::cout);
  }
}
