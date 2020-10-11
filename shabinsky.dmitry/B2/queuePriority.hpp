//
// Created by sdimosik on 11.10.2020.
//

#ifndef B2_QUEUEPRIORITY_HPP
#define B2_QUEUEPRIORITY_HPP

#include <list>
#include <stdexcept>

template<typename T>
class QueuePriority
{
public:
  enum class Priority
  {
    LOW, NORMAL, HIGH
  };
  
  void add(const T &element, Priority type);
  
  T get();
  
  void accelerate();
  
  bool isEmpty() const noexcept;

private:
  std::list<T> low_;
  std::list<T> normal_;
  std::list<T> high_;
};

template<typename T>
void QueuePriority<T>::add(const T &element, QueuePriority::Priority type)
{
  switch (type)
  {
    case Priority::HIGH:
    {
      high_.push_back(element);
      break;
    }
    case Priority::NORMAL:
    {
      normal_.push_back(element);
      break;
    }
    case Priority::LOW:
    {
      low_.push_back(element);
      break;
    }
    default:
    {
    }
  }
}

template<typename T>
T QueuePriority<T>::get()
{
  if (!high_.empty())
  {
    return high_.back();
  }
  else if (!normal_.empty())
  {
    return normal_.back();
  }
  else if (!low_.empty())
  {
    return low_.back();
  }
  throw std::logic_error("QueuePriority is empty");
}

template<typename T>
bool QueuePriority<T>::isEmpty() const noexcept
{
  return low_.empty() && normal_.empty() && high_.empty();
}

template<typename T>
void QueuePriority<T>::accelerate()
{
  high_.splice(high_.end(), low_);
}

#endif //B2_QUEUEPRIORITY_HPP
