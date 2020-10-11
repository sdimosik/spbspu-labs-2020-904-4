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
  
  T get();
  
  void accelerate();
  
  bool isEmpty() const noexcept;

private:
  std::list<T> low_;
  std::list<T> normal_;
  std::list<T> high_;
};

template<typename T>
void queuePriority<T>::add(const T &element, queuePriority::Priority type)
{
  switch (type)
  {
    case Priority::HIGH:
    {
      high_.push_front(element);
      break;
    }
    case Priority::NORMAL:
    {
      normal_.push_front(element);
      break;
    }
    case Priority::LOW:
    {
      low_.push_front(element);
      break;
    }
    default:
    {
    }
  }
}

template<typename T>
T queuePriority<T>::get()
{
  std::list<T> *element = nullptr;
  if (!high_.empty())
  {
    element = &high_;
  }
  else if (!normal_.empty())
  {
    element = &normal_;
  }
  else if (!low_.empty())
  {
    element = &low_;
  }
  if (element)
  {
    T result = element->back();
    element->pop_back();
    return result;
  }
  throw std::logic_error("queuePriority is empty");
}

template<typename T>
bool queuePriority<T>::isEmpty() const noexcept
{
  return low_.empty() && normal_.empty() && high_.empty();
}

template<typename T>
void queuePriority<T>::accelerate()
{
  if (!low_.empty())
  {
    high_.splice(high_.begin(), low_);
  }
}

#endif //B2_QUEUEPRIORITY_HPP
