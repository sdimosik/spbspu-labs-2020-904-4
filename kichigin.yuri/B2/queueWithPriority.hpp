#ifndef QUEUE_WITH_PRIORITY
#define QUEUE_WITH_PRIORITY
#include <list>
#include <stdexcept>

template <class elemType>
class QueueWithPriority
{
public:
  enum class ElementPriority
  {
    LOW,
    NORMAL,
    HIGH
  };

  bool empty() const noexcept;
  void putElementToQueue(const elemType& element, const ElementPriority priority);
  const elemType getElementFromQueue() const;
  void removeElementFromQueue() noexcept;
  void accelerate() noexcept;

private:
  const static size_t numberOfPriorities_ = 3;
  std::list<elemType> queueArray_[numberOfPriorities_];
};


template<class elemType>
bool QueueWithPriority<elemType>::empty() const noexcept
{
  for (size_t i = 0; i < numberOfPriorities_; ++i)
  {
    if (!queueArray_[i].empty())
    {
      return false;
    }
  }
  return true;
}

template<class elemType>
void QueueWithPriority<elemType>::putElementToQueue(const elemType& element, const ElementPriority priority)
{
  if (static_cast<size_t>(priority) < numberOfPriorities_)
  {
    queueArray_[numberOfPriorities_ - static_cast<size_t>(priority) - 1].push_back(element);
  }
  else
  {
    throw std::invalid_argument("Unknown priority");
  }
}

template<class elemType>
const elemType QueueWithPriority<elemType>::getElementFromQueue() const
{
  for (size_t i = 0; i < numberOfPriorities_; ++i)
  {
    if (!queueArray_[i].empty())
    {
      return queueArray_[i].front();
    }
  }
  throw std::underflow_error("Queue with priotity is empty");
}

template<class elemType>
void QueueWithPriority<elemType>::removeElementFromQueue() noexcept
{
  for (size_t i = 0; i < numberOfPriorities_; ++i)
  {
    if (!queueArray_[i].empty())
    {
      return queueArray_[i].pop_front();
    }
  }
}

template<class elemType>
void QueueWithPriority<elemType>::accelerate() noexcept
{
  if (!queueArray_[numberOfPriorities_ - 1].empty())
  {
    queueArray_[0].splice(queueArray_[0].end(), queueArray_[numberOfPriorities_ - 1]);
  }
}

#endif // !QUEUE_WITH_PRIORITY
