#ifndef QUEUEWITHPRIORITY_HPP
#define QUEUEWITHPRIORITY_HPP

#include <list>
#include <stdexcept>

template <typename T>
class QueueWithPriority
{
public:

  enum class ElementPriority
  {
    LOW,
    NORMAL,
    HIGH,
    SIZE
  };

  void putElementToQueue(const T & element, ElementPriority priority);

  T getElementFromQueue();

  void popElementFromQueue();

  bool isEmpty() noexcept;

  void accelerate();

private:

  std::list<T> priorities_[static_cast<size_t>(ElementPriority::SIZE)];
};

template<typename T>
void QueueWithPriority<T>::putElementToQueue(const T &element, ElementPriority priority)
{
  priorities_[static_cast<int>(priority)].push_back(element);
}

template<typename T>
void QueueWithPriority<T>::popElementFromQueue()
{
  if(isEmpty())
  {
    throw std::runtime_error("Queue is empty");
  }

  for(size_t i = static_cast<size_t>(ElementPriority::SIZE) - 1; i >= 0; i--)
  {
    if(!priorities_[i].empty())
    {
      priorities_[i].pop_front();
      return;
    }
  }
}

template<typename T>
T QueueWithPriority<T>::getElementFromQueue()
{
  if(isEmpty())
  {
    throw std::runtime_error("Queue is empty");
  }

  for(size_t i = static_cast<size_t>(ElementPriority::SIZE) - 1; i >= 0; i--)
  {
    if(!priorities_[i].empty())
    {
      return priorities_[i].front();
    }
  }
}

template<typename T>
void QueueWithPriority<T>::accelerate()
{
  priorities_[static_cast<size_t>(ElementPriority::SIZE) - 1].splice(priorities_[static_cast<size_t>(ElementPriority::SIZE) - 1].end(), priorities_[0]);
}

template<typename T>
bool QueueWithPriority<T>::isEmpty() noexcept
{
  for (size_t i = 0; i <= static_cast<size_t>(ElementPriority::SIZE) - 1; i++)
  {
    if (!priorities_[i].empty())
    {
      return false;
    }
  }
  return true;
}

#endif
