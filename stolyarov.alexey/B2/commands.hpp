#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include "queueWithPriority.hpp"

namespace commands
{
  template <typename T>
  void add(QueueWithPriority<T>& queue, std::istream& fin, std::ostream& fout);

  template <typename T>
  void get(QueueWithPriority<T>& queue, std::ostream& fout);

  template <typename T>
  void accelerate(QueueWithPriority<T>& queue);

  template <typename T>
  void print(typename std::list<T>::iterator begin, typename std::list<T>::iterator end);

  template<typename T>
  void add(QueueWithPriority<T>& queue, std::istream& fin, std::ostream& fout)
  {
    std::string typeIn, element, buffer;
    fin >> typeIn;
    fin >> element;

    if (!fin.eof())
    {
      std::getline(fin, buffer);
    }

    element += buffer;

    if (typeIn.empty() || element.empty())
    {
      fout << "<INVALID COMMAND>" << '\n';
      return;
    }

    typename QueueWithPriority<T>::QueuePriority queueType;

    if (typeIn == "high")
    {
      queueType = QueueWithPriority<T>::QueuePriority::HIGH;
    }
    else if (typeIn == "normal")
    {
      queueType = QueueWithPriority<T>::QueuePriority::NORMAL;
    }
    else if (typeIn == "low")
    {
      queueType = QueueWithPriority<T>::QueuePriority::LOW;
    }
    else
    {
      fout << "<INVALID COMMAND>" << '\n';
      return;
    }
    queue.add(element, queueType);
  }

  template<typename T>
  void get(QueueWithPriority<T>& queue, std::ostream& fout)
  {
    if (queue.isEmpty())
    {
      fout << "<EMPTY>" << '\n';
      return;
    }
    T element;
    queue.get(element);
    fout << element << '\n';
  }

  template <typename T>
  void accelerate(QueueWithPriority<T>& queue)
  {
    queue.accelerate();
  }

  template <typename T>
  void print(typename std::list<T>::iterator begin, typename std::list<T>::iterator end)
  {
    if (begin == end)
    {
      std::cout << "\n";
      return;
    }
    if (begin == std::prev(end))
    {
      std::cout << *begin << '\n';
      return;
    }
    std::cout << *begin++ << ' ' << *std::prev(end--) << ' ';
    print<T>(begin, end);
  }
}

#endif
