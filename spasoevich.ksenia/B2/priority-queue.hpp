#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include<list>
#include<iostream>
#include<stdexcept>

template<typename T>
class priorityQueue
{
public:
  enum ElementPriority
  {
    LOW,
    NORMAL,
    HIGH
  };

  void addElementToQueue(const T& element, const ElementPriority priority);
  void deleteElementFromQueue();
  T getElementFromQueue() const;
  bool isEmpty() const noexcept;
  void accelerate();

private:
  static const size_t PRIORITIES=3;
  std::list<T> lists_[PRIORITIES];
};

template<typename T>
void priorityQueue<T>::addElementToQueue(const T& element, const ElementPriority priority)
{
  lists_[priority].push_back(element);
}

template<typename T>
void priorityQueue<T>::deleteElementFromQueue()
{
  if(isEmpty())
  {
    throw std::out_of_range("Queue is empty");
  }
  for(size_t i = PRIORITIES - 1; i >= 0; i--)
  {
    if(!lists_[i].empty())
    {
      lists_[i].pop_front();
      break;
    }
  }
}

template<typename T>
T priorityQueue<T>::getElementFromQueue() const
{
  for (size_t i = PRIORITIES - 1; i >= 0; --i)
  {
    if (!lists_[i].empty())
    {
      return lists_[i].front();
    }
  }
  throw std::out_of_range("Queue is empty");

}

template<typename T>
bool priorityQueue<T>::isEmpty() const noexcept
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

template<typename T>
void priorityQueue<T>::accelerate()
{
  lists_[PRIORITIES - 1].splice(lists_[PRIORITIES - 1].end(), lists_[0]);
}

#endif


