#ifndef SPBSPU_LABS_2020_904_4_QUEUEWITHPRIORITY_HPP
#define SPBSPU_LABS_2020_904_4_QUEUEWITHPRIORITY_HPP

#include <list>
#include <stdexcept>

template <typename QueueElement>
class QueueWithPriority
{
public:
  enum class ElementPriority : size_t
  {
    LOW,
    NORMAL,
    HIGH
  };

  void PutElementToQueue(const QueueElement & element, ElementPriority priority);

  QueueElement GetElementFromQueue();

  void Accelerate();

  bool Empty();

  void PopFront();

private:
  static const size_t PRIORITIES = 3;
  std::list<QueueElement> lists_[PRIORITIES];
};

template <typename QueueElement>
void QueueWithPriority<QueueElement>::PutElementToQueue(const QueueElement &element, ElementPriority priority)
{
  lists_[int(priority)].push_back(element);
}

template <typename QueueElement>
QueueElement QueueWithPriority<QueueElement>::GetElementFromQueue()
{
  if (Empty())
  {
    throw std::out_of_range("Queue is empty!\n");
  }
  for(size_t i = PRIORITIES - 1; i >= 0; --i)
  {
    if(!lists_[i].empty())
    {
      return lists_[i].front();
    }
  }
}

template <typename QueueElement>
void QueueWithPriority<QueueElement>::Accelerate()
{
  if(!lists_[0].empty())
  {
    lists_[PRIORITIES - 1].splice(lists_[PRIORITIES - 1].end(), lists_[0]);
  }
}

template <typename QueueElement>
bool QueueWithPriority<QueueElement>::Empty()
{
  for(size_t i = 0; i < PRIORITIES; ++i)
  {
    if(!lists_[i].empty())
    {
      return false;
    }
  }
  return true;
}

template <typename QueueElement>
void QueueWithPriority<QueueElement>::PopFront()
{
  if(Empty())
  {
    throw std::out_of_range("Queue is empty!\n");
  }
  for(size_t i = PRIORITIES - 1; i >= 0; --i)
  {
    if(!lists_[i].empty())
    {
      lists_[i].pop_front();
      break;
    }
  }
}

#endif
