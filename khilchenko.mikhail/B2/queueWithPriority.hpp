#ifndef QUEUE_WITH_PRIORITY
#define QUEUE_WITH_PRIORITY

#include <list>
#include <exception>
#include <iostream>

template <typename T>
class QueueWithPriority
{
public:

  typedef enum
  {
    LOW,
    NORMAL,
    HIGH
  } ElementPriority;

  void putElementToQueue(const T& element, ElementPriority priority);
  T getFirstElement() const;
  void removeFirstElement();
  void accelerate();
  bool isEmpty() const noexcept;

private:
  static const size_t numberOfLists = 3;
  std::list<T> lists_[numberOfLists];
};

template <typename T>
void QueueWithPriority<T>::putElementToQueue(const T& element, ElementPriority priority)
{
  lists_[priority].push_back(element);
}

template <typename T>
T QueueWithPriority<T>::getFirstElement() const
{
  for(size_t i = numberOfLists - 1; i >= 0; i--)
  {
    if(!lists_[i].empty())
    {
      return lists_[i].front();
    }
  }
  throw std::logic_error("QueueWithPriority is empty");
}

template <typename T>
void QueueWithPriority<T>::removeFirstElement()
{
  if(isEmpty())
  {
    throw std::logic_error("QueueWithPriority is empty");
  }
  for(size_t i = numberOfLists - 1; i >= 0; i--)
  {
    if(!lists_[i].empty())
    {
      lists_[i].pop_front();
      break;
    }
  }
}

template <typename T>
void QueueWithPriority<T>::accelerate()
{
  lists_[HIGH].splice(lists_[HIGH].end(), lists_[LOW]);
}

template <typename T>
bool QueueWithPriority<T>::isEmpty() const noexcept
{
  for(size_t i = 0; i < numberOfLists; i++)
  {
    if(!lists_[i].empty())
    {
      return false;
    }
  }
  return true;
}

#endif
