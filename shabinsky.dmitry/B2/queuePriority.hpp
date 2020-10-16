//
// Created by sdimosik on 11.10.2020.
//

#ifndef B2_QUEUEPRIORITY_HPP
#define B2_QUEUEPRIORITY_HPP

#include <list>
#include <stdexcept>

template<typename T>
class queuePriority
{
public:
  enum class Priority
  {
    LOW, NORMAL, HIGH
  };
  
  void add(const T &element, Priority type);
  
  void get(T &element);
  
  void accelerate();
  
  bool isEmpty() const noexcept;

private:
  static const size_t NUMBER_OF_LEVELS = 3;
  std::list<T> data_[NUMBER_OF_LEVELS];
};

template<typename T>
void queuePriority<T>::add(const T &element, const queuePriority::Priority type)
{
  if (static_cast<size_t>(type) >= 0 && static_cast<size_t>(type) < NUMBER_OF_LEVELS)
  {
    data_[static_cast<size_t>(type)].push_front(element);
  }
  else
  {
    throw std::invalid_argument("Unknown type");
  }
}

template<typename T>
void queuePriority<T>::get(T &element)
{
  for (size_t i = NUMBER_OF_LEVELS - 1; i >= 0; --i)
  {
    if (!data_[i].empty())
    {
      element = data_[i].back();
      data_[i].pop_back();
      return;
    }
  }
  throw std::logic_error("queuePriority is empty");
}

template<typename T>
bool queuePriority<T>::isEmpty() const noexcept
{
  for (size_t i = 0; i <= NUMBER_OF_LEVELS - 1; i++)
  {
    if (!data_[i].empty())
    {
      return false;
    }
  }
  return true;
  
}

template<typename T>
void queuePriority<T>::accelerate()
{
  data_[NUMBER_OF_LEVELS - 1].splice(data_[NUMBER_OF_LEVELS - 1].begin(), data_[0]);
}

#endif //B2_QUEUEPRIORITY_HPP
