#ifndef LABS_PRIORITY_QUEUE_HPP
#define LABS_PRIORITY_QUEUE_HPP
#include <stdexcept>
#include <string>
#include <list>

namespace detail
{
  template<typename ElementType>
  class QueueWithPriority
  {
  public:
    enum Priority
    {
      LOW,
      NORMAL,
      HIGH,
      PRIORITY_LEVELS
    };

    void putElementToQueue(const ElementType& element, Priority priority);
    void getElementFromQueue(ElementType& element);
    void accelerate();
    bool isEmpty() const noexcept;

  private:
    //static const int PRIORITY_LEVELS = 3;
    std::list<ElementType> priority_[PRIORITY_LEVELS];
  };
}

template<typename ElementType>
void detail::QueueWithPriority<ElementType>::putElementToQueue(const ElementType& element, Priority priority)
{
  priority_[priority].push_back(element);
}

template<typename ElementType>
void detail::QueueWithPriority<ElementType>::getElementFromQueue(ElementType& element)
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

template<typename ElementType>
void detail::QueueWithPriority<ElementType>::accelerate()
{
  priority_[PRIORITY_LEVELS - 1].splice(priority_[PRIORITY_LEVELS - 1].end(), priority_[0]);
}

template<typename T>
bool detail::QueueWithPriority<T>::isEmpty() const noexcept
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
