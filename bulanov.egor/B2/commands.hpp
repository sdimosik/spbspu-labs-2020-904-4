#ifndef SPBSPU_LABS_2020_904_4_COMMANDS_HPP
#define SPBSPU_LABS_2020_904_4_COMMANDS_HPP

#include <iostream>
#include <sstream>
#include <cstring>
#include "queueWithPriority.hpp"

template<typename T>
void choiceCommand(const std::string &command, QueueWithPriority<T> &queue, std::stringstream &in, std::ostream &out)
{
  if (command == "add")
  {
    executeAdd(queue, in, out);
    return;
  }

  if (command == "get")
  {
    executeGet(queue, in, out);
    return;
  }

  if (command == "accelerate")
  {
    executeAccelerate(queue, in, out);
    return;
  }

  out << "<INVALID COMMAND>" << '\n';
}


template<class T>
void executeAdd(QueueWithPriority<T> &queue, std::stringstream &in, std::ostream &out)
{
  std::string priorityData;
  in >> std::ws >> priorityData;
  T data;
  std::getline(in >> std::ws, data, '\0');

  if (data.empty())
  {
    out << "<INVALID COMMAND>" << '\n';
    return;
  }

  if (priorityData == "high")
  {
    queue.putElementToQueue(data, QueueWithPriority<T>::HIGH);
    return;
  }
  if (priorityData == "normal")
  {
    queue.putElementToQueue(data, QueueWithPriority<T>::NORMAL);
    return;
  }
  if (priorityData == "low")
  {
    queue.putElementToQueue(data, QueueWithPriority<T>::LOW);
    return;
  }
  else
  {
    out << "<INVALID COMMAND>" << '\n';
    return ;
  }
}

template<class T>
void executeGet(QueueWithPriority<T> &queue, std::stringstream &in, std::ostream &out)
{
  in >> std::ws;
  if (!in.eof())
  {
    out << "<INVALID COMMAND>" << '\n';
    return;
  }

  if (queue.isEmpty())
  {
    out << "<EMPTY>" << '\n';
    return;
  }

  T element;
  queue.pullElementFromQueue(element);
  out << element << '\n';
}

template<class T>
void executeAccelerate(QueueWithPriority<T> &queue, std::stringstream &in, std::ostream &out)
{
  if (!in.eof())
  {
    out << "<INVALID COMMAND>" << '\n';
    return;
  }

  queue.accelerate();
}

#endif
