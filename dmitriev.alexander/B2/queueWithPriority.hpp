#ifndef QUEUEWITHPRIORITY_HPP
#define QUEUEWITHPRIORITY_HPP

#include <list>
#include <stdexcept>

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

  bool isEmpty() const;

private:
  static const int PRIORITY_COUNT = 3;

  std::list<T> priorityList_[PRIORITY_COUNT];
};

template<typename T>
void QueueWithPriority<T>::putElementToQueue(const T &element, ElementPriority priority)
{
  priorityList_[priority].push_back(element);
}

template<typename T>
void QueueWithPriority<T>::getElementFromQueue(T &element)
{
  if (isEmpty())
  {
    throw std::runtime_error("Queue is empty!");
  }

  for (int priority = PRIORITY_COUNT - 1; priority >= 0; priority--)
  {
    if (!priorityList_[priority].empty())
    {
      element = priorityList_[priority].front();
      priorityList_[priority].pop_front();
      return;
    }
  }
}

template<typename T>
void QueueWithPriority<T>::accelerate()
{
  priorityList_[PRIORITY_COUNT - 1].splice(priorityList_[PRIORITY_COUNT - 1].end(), priorityList_[0]);
}

template<typename T>
bool QueueWithPriority<T>::isEmpty() const
{
  for (int priority = PRIORITY_COUNT - 1; priority >= 0; priority--)
  {
    if (!priorityList_[priority].empty())
    {
      return false;
    }
  }
  return true;
}

#endif
