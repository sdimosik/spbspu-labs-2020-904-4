#ifndef LUBS_FUNCTIONS_HPP
#define LUBS_FUNCTIONS_HPP
#include <iostream>
#include <sstream>
#include "priority-queue.hpp"

#define INVALID_COMMAND_N "<INVALID COMMAND>\n"
#define EMPTY_N "<EMPTY>\n"
#define INVALID_COMMAND "<INVALID COMMAND>"
#define EMPTY "<EMPTY>"

namespace detail {
  template <class T>
  void add(detail::QueueWithPriority<T>& queue, std::stringstream& stringStream, std::ostream& out)
  {
    T data;
    std::string priority;

    stringStream >> std::ws;
    stringStream >> priority;

    stringStream >> std::ws;
    std::getline(stringStream, data, '\0');

    if (data.empty())
    {
      out << INVALID_COMMAND_N;
      return;
    }

    if (priority == "high")
    {
      queue.putElementToQueue(data, detail::QueueWithPriority<T>::HIGH);
      return;
    }
    if (priority == "normal")
    {
      queue.putElementToQueue(data, detail::QueueWithPriority<T>::NORMAL);
      return;
    }
    if (priority == "low")
    {
      queue.putElementToQueue(data, detail::QueueWithPriority<T>::LOW);
      return;
    }
    out << INVALID_COMMAND_N;
  }

  template <class T>
  void get(detail::QueueWithPriority<T>& queue, std::stringstream& stringStream, std::ostream& out)
  {
    stringStream >> std::ws;
    if (!stringStream.eof())
    {
      out << INVALID_COMMAND_N;
      return;
    }

    if (queue.isEmpty())
    {
      out << EMPTY_N;
      return;
    }
    T element;
    queue.getElementFromQueue(element);
    out << element << '\n';
  }

  template <class T>
  void accelerate(detail::QueueWithPriority<T>& queue, std::stringstream& stringStream, std::ostream& out)
  {
    if (!stringStream.eof())
    {
      out << INVALID_COMMAND_N;
      return;
    }
    queue.accelerate();
  }

  template<typename T>
  void parseCommand(const std::string& command, detail::QueueWithPriority<T>& queue, std::stringstream& stringStream, std::ostream& out)
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
    out << INVALID_COMMAND_N;
  }
}
#endif
