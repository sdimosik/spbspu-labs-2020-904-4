#ifndef B2_QUEUEWITHPRIORITY_HPP
#define B2_QUEUEWITHPRIORITY_HPP

#include <iostream>
#include <list>

template<typename T>
class QueueWithPriority
{
public:

  typedef enum
  {
    LOW_PRIORITY,
    NORMAL_PRIORITY,
    HIGH_PRIORITY
  } ElementPriority;

  void putElementToQueue(const T &element, ElementPriority priority);

  void getElementFromQueue(T &element);

  void accelerate();

  bool isEmpty() const noexcept;

private:
  static const int PRIORITY_LEVELS = 3;

  std::list<T> priority_[PRIORITY_LEVELS];
};

template<typename T>
void QueueWithPriority<T>::putElementToQueue(const T &element, ElementPriority priority)
{
  priority_[priority].push_back(element);
}

template<typename T>
void QueueWithPriority<T>::getElementFromQueue(T &element)
{
  if (isEmpty())
  {
    throw std::runtime_error("Queue is isEmpty!");
  }

  for (size_t i = PRIORITY_LEVELS - 1; i >= 0; i--)
  {
    if (!priority_[i].empty())
    {
      element = priority_[i].front();
      priority_[i].pop_front();
      return;
    }
  }
}

template<typename T>
void QueueWithPriority<T>::accelerate()
{
  priority_[PRIORITY_LEVELS - 1].splice(priority_[PRIORITY_LEVELS - 1].end(), priority_[0]);
}

template<typename T>
bool QueueWithPriority<T>::isEmpty() const noexcept
{
  for (size_t i = 0; i <= PRIORITY_LEVELS - 1; i++)
  {
    if (!priority_[i].empty())
    {
      return false;
    }
  }
  return true;
}

#endif
