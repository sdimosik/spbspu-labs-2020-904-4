#ifndef B2_PARSECOMMAND_HPP
#define B2_PARSECOMMAND_HPP
#include <iostream>
#include <sstream>
#include "queueWithPriority.hpp"

template <class T>
void add(QueueWithPriority<T> &queue, std::stringstream &stringStream, std::ostream &out);

template <class T>
void get(QueueWithPriority<T> &queue, std::stringstream &stringStream, std::ostream &out);

template <class T>
void accelerate(QueueWithPriority<T> &queue, std::stringstream &stringStream, std::ostream &out);

template<typename T>
void parseCommand(const std::string &command, QueueWithPriority<T> &queue,
    std::stringstream &stringStream, std::ostream &out)
{
  if (command == "add")
  {
    add(queue, stringStream, out);
    return;
  }

  if (command == "get")
  {
    get(queue, stringStream, out);
    return;
  }

  if (command == "accelerate")
  {
    accelerate(queue, stringStream, out);
    return;
  }

  out << "<INVALID COMMAND>" << '\n';
}

template <class T>
void add(QueueWithPriority<T> &queue, std::stringstream &stringStream, std::ostream &out)
{
  T data;
  std::string priority;

  stringStream >> std::ws;
  stringStream >> priority;

  stringStream >> std::ws;
  std::getline(stringStream, data, '\0');

  if (data.empty())
  {
    out << "<INVALID COMMAND>\n";
    return;
  }

  if (priority == "high")
  {
    queue.putElementToQueue(data, QueueWithPriority<T>::HIGH_PRIORITY);
    return;
  }
  if (priority == "normal")
  {
    queue.putElementToQueue(data, QueueWithPriority<T>::NORMAL_PRIORITY);
    return;
  }
  if (priority == "low")
  {
    queue.putElementToQueue(data, QueueWithPriority<T>::LOW_PRIORITY);
    return;
  }
  out << "<INVALID COMMAND>" << '\n';
}

template <class T>
void get(QueueWithPriority<T> &queue, std::stringstream &stringStream, std::ostream &out)
{
  stringStream >> std::ws;
  if (!stringStream.eof())
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
  queue.getElementFromQueue(element);
  out << element << '\n';
}

template <class T>
void accelerate(QueueWithPriority<T> &queue, std::stringstream &stringStream, std::ostream &out)
{
  if (!stringStream.eof())
  {
    out << "<INVALID COMMAND>" << '\n';
    return;
  }
  queue.accelerate();
}
#endif
