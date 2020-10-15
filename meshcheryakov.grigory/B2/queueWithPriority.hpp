#ifndef SPBSPU_LABS_2020_904_4_QUEUEWITHPRIORITY_HPP
#define SPBSPU_LABS_2020_904_4_QUEUEWITHPRIORITY_HPP

#include <iostream>
#include <list>

template<typename T>
class QueueWithPriority
{
public:

  using elementPriority = enum {LOW, NORMAL, HIGH};

  void putElementToQueue(const T &element, elementPriority priority);

  T getElementFromQueue();

  void popElementFromQueue();

  void accelerate();

  bool isEmpty() const noexcept;

private:
  std::list<T> high_;
  std::list<T> normal_;
  std::list<T> low_;
};

template<typename T>
void QueueWithPriority<T>::putElementToQueue(const T &element, elementPriority priority)
{
  switch (priority)
  {
    case HIGH:
      high_.push_back(element);
      break;
    case NORMAL:
      normal_.push_back(element);
      break;
    case LOW:
      low_.push_back(element);
      break;
  }
}

template<typename T>
T QueueWithPriority<T>::getElementFromQueue()
{
  if (!high_.empty())
  {
    return high_.front();
  }

  if (!normal_.empty())
  {
    return normal_.front();
  }

  if (!low_.empty())
  {
    return low_.front();
  }
  throw std::logic_error("Queue is empty");
}

template<typename T>
void QueueWithPriority<T>::popElementFromQueue()
{
  if (!high_.empty())
  {
    high_.pop_front();
    return;
  }

  if (!normal_.empty())
  {
    normal_.pop_front();
    return;
  }

  if (!low_.empty())
  {
    low_.pop_front();
    return;
  }

  throw std::logic_error("Queue is empty");
}

template<typename T>
void QueueWithPriority<T>::accelerate()
{
  if (!low_.empty())
  {
    high_.splice(high_.end(), low_);
  }
}

template<typename T>
bool QueueWithPriority<T>::isEmpty() const noexcept
{
  return (high_.empty() && normal_.empty() && low_.empty());
}

#endif
