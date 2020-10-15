#ifndef QUEUE_WITH_PRIORITY_HPP
#define QUEUE_WITH_PRIORITY_HPP
#include <stdexcept>
#include <list>
#include <cstddef>

template <typename T>
class  QueueWithPriority
{
public:
  enum ElementPriority : size_t
  {
    LOW,
    NORMAL,
    HIGH
  };
  void add(ElementPriority priority, const T& element);
  T get() const;
  void accelerate();
  bool isEmpty() const noexcept;
  void pop();
private:
  static const size_t PRIORITIES = 3;
  std::list<T> lists_[PRIORITIES];
};

template <typename T>
void QueueWithPriority<T>::add(ElementPriority priority, const T& element)
{
  lists_[priority].push_back(element);
}

template <typename T>
T QueueWithPriority<T>::get() const
{
  if (isEmpty())
  {
    throw std::out_of_range("Empty queue");
  }
  for (int i = PRIORITIES - 1; i >= 0; i--)
  {
    if (!lists_[i].empty())
    {
      const T temp = lists_[i].front();
      return temp;
    }
  }
  throw std::runtime_error("Error while getting element from queue");
}

template <typename T>
void QueueWithPriority<T>::accelerate()
{
  lists_[PRIORITIES - 1].splice(lists_[PRIORITIES - 1].end(), lists_[0]);
}

template <typename T>
bool QueueWithPriority<T>::isEmpty() const noexcept
{
  for (int i = PRIORITIES - 1; i >= 0; i--)
  {
    if (!lists_[i].empty())
    {
      return false;
    }
  }
  return true;
}

template <typename T>
void QueueWithPriority<T>::pop()
{
  if (isEmpty())
  {
    throw std::out_of_range("Empty queue");
  }
  for (int i = PRIORITIES - 1; i >= 0; i--)
  {
    if (!lists_[i].empty())
    {
      lists_[i].pop_front();
      break;
    }
  }
}

#endif
