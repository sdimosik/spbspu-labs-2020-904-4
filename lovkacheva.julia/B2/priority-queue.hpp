#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <string>
#include <list>
#include <stdexcept>
#include <array>

namespace lovkacheva
{
  template<class QueueElement>
  class PriorityQueue
  {
  public:

    enum class ElementPriority
    {
      HIGH,
      NORMAL,
      LOW
    };

    void put(const QueueElement& element, ElementPriority priority);

    QueueElement front() const;

    void pop();

    void accelerate();

    size_t size() const noexcept;

    bool empty() const noexcept;

  private:
    using List = std::list<QueueElement>;
    static const size_t DEFAULT_PRIORITY_NUMBER = 3;
    std::array<List, DEFAULT_PRIORITY_NUMBER> priorities_;
  };

  template<class QueueElement>
  bool PriorityQueue<QueueElement>::empty() const noexcept
  {
    for (const List& priority : priorities_)
    {
      if (!priority.empty())
      {
        return false;
      }
    }
    return true;
  }

  template<class QueueElement>
  void PriorityQueue<QueueElement>::accelerate()
  {
    priorities_[static_cast<size_t>(ElementPriority::HIGH)].splice(priorities_[static_cast<size_t>(ElementPriority::HIGH)].end(), priorities_[static_cast<size_t>(ElementPriority::LOW)]);
  }

  template<class QueueElement>
  size_t PriorityQueue<QueueElement>::size() const noexcept
  {
    size_t result = 0;
    for (const List& priority : priorities_)
    {
      result += priority.size();
    }
    return result;
  }

  template<class QueueElement>
  QueueElement PriorityQueue<QueueElement>::front() const
  {
    const List *currentPriority = nullptr;
    for (const List& priority : priorities_)
    {
      if (!priority.empty())
      {
        currentPriority = &priority;
        break;
      }
    }
    if (currentPriority)
    {
      QueueElement result = currentPriority->front();
      return result;
    }
    throw std::runtime_error("Can't examine the front of an empty queue");
  }

  template <class QueueElement>
  void PriorityQueue<QueueElement>::pop()
  {
    List *currentPriority = nullptr;
    for (List& priority : priorities_)
    {
      if (!priority.empty())
      {
        currentPriority = &priority;
        break;
      }
    }
    if (currentPriority)
    {
      currentPriority->pop_front();
    }
    else
    {
      throw std::runtime_error("Can't pop an element: the queue is empty");
    }
  }

  template<class QueueElement>
  void PriorityQueue<QueueElement>::put(const QueueElement& element, ElementPriority priority)
  {
    priorities_[static_cast<size_t>(priority)].push_back(element);
  }
}
#endif
