//
// Created by sdimosik on 11.10.2020.
//

#ifndef B2_UTILS_HPP
#define B2_UTILS_HPP

#include "queuePriority.hpp"
#include <sstream>
#include <iostream>

namespace utils
{
  const char *INVALID_COMMAND = "<INVALID COMMAND>";
  
  template<class T>
  void add(queuePriority<T> &queue, std::stringstream &in, std::ostream &out);
  
  template<class T>
  void get(queuePriority<T> &queue, std::ostream &out);
  
  template<class T>
  void accelerate(queuePriority<T> &queue);
  
  template<class T>
  void print(typename std::list<T>::iterator begin, typename std::list<T>::iterator end);
  
  template<class T>
  void add(queuePriority<T> &queue, std::stringstream &in, std::ostream &out)
  {
    std::string typeIn, element, buffer;
    in >> typeIn;
    in >> element;
    
    if (!in.eof())
    {
      std::getline(in, buffer);
    }
    
    element += buffer;
    
    if (typeIn.empty() || element.empty())
    {
      out << INVALID_COMMAND << '\n';
      return;
    }
    
    typename queuePriority<T>::Priority type;
    
    if (typeIn == "high")
    {
      type = queuePriority<T>::Priority::HIGH;
    }
    else if (typeIn == "normal")
    {
      type = queuePriority<T>::Priority::NORMAL;
    }
    else if (typeIn == "low")
    {
      type = queuePriority<T>::Priority::LOW;
    }
    else
    {
      out << INVALID_COMMAND << '\n';
      return;
    }
    queue.add(element, type);
  }
  
  template<class T>
  void get(queuePriority<T> &queue, std::ostream &out)
  {
    if (queue.isEmpty())
    {
      out << "<EMPTY>" << '\n';
      return;
    }
    T element;
    queue.get(element);
    out << element << '\n';
  }
  
  template<class T>
  void accelerate(queuePriority<T> &queue)
  {
    queue.accelerate();
  }
  
  template<class T>
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

#endif //B2_UTILS_HPP
