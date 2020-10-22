#ifndef SPBSPU_LABS_2020_904_4_QUEUEWITHPRIORITY_HPP
#define SPBSPU_LABS_2020_904_4_QUEUEWITHPRIORITY_HPP

#include <list>
#include <stdexcept>

template<typename T>
class QueueWithPriority
{
public:

  typedef enum
  {
    LOW,
    NORMAL,
    HIGH,
    QUANTITY
  } ElementPriority;

  void putElementToQueue(const T &element, ElementPriority priority);

  void pullElementFromQueue(T &element);

  bool isEmpty() const noexcept;

  void accelerate();

private:
  std::list<T> priorityVar_[QUANTITY];
};

template<typename T>
void QueueWithPriority<T>::putElementToQueue(const T &element, ElementPriority priority)
{
  priorityVar_[priority].push_back(element);
}

template<typename T>
void QueueWithPriority<T>::pullElementFromQueue(T &element)
{
  if(isEmpty())
  {
    throw std::runtime_error("Error: queue is empty!");
  }
  else
  {
    for (size_t i = QUANTITY - 1; i >= 0; i--)
    {
      if (!priorityVar_[i].empty())
      {
        element = priorityVar_[i].front();
        priorityVar_[i].pop_front();
        return;
      }
    }
  }
}

template<typename T>
bool QueueWithPriority<T>::isEmpty() const noexcept
{
  for (size_t i = 0; i <= QUANTITY - 1; i++)
  {
    if (!priorityVar_[i].empty())
    {
      return false;
    }
  }
  return true;
}

template<typename T>
void QueueWithPriority<T>::accelerate()
{
  priorityVar_[QUANTITY - 1].splice(priorityVar_[QUANTITY - 1].end(), priorityVar_[0]);
}


#endif
