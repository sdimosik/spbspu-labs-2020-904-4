#ifndef QUEUE_WITH_PRIORITY_HPP
#define QUEUE_WITH_PRIORITY_HPP

#include <list>
#include <stdexcept>

template <typename T>
class QueueWithPriority
{
public:
  enum class QueuePriority
  {
    LOW,
    NORMAL,
    HIGH,
    PRIORITY_NUMBERS
  };

  void add(const T& element, QueuePriority priority);

  void get(T& element);

  void accelerate() noexcept;

  bool isEmpty() const noexcept;

private:
  std::list<T> data_[static_cast<size_t>(QueuePriority::PRIORITY_NUMBERS)];
};

template<typename T>
void QueueWithPriority<T>::add(const T& element, QueuePriority priority)
{
  if (static_cast<size_t>(priority) >= 0 && static_cast<size_t>(priority) < static_cast<size_t>(QueuePriority::PRIORITY_NUMBERS))
  {
    data_[static_cast<size_t>(priority)].push_front(element);
  }
  else
  {
    throw std::invalid_argument("QueueWithPriority: Invalid type of priority");
  }
}

template <typename T>
void QueueWithPriority<T>::get(T& element)
{
  for (size_t i = static_cast<size_t>(QueuePriority::PRIORITY_NUMBERS) - 1; i >= 0; --i)
  {
    if (!data_[i].empty())
    {
      element = data_[i].back();
      data_[i].pop_back();
      return;
    }
  }
  throw std::logic_error("QueueWithPriority: Queue is empty");
}

template <typename T>
void QueueWithPriority<T>::accelerate() noexcept
{
  data_[static_cast<size_t>(QueuePriority::PRIORITY_NUMBERS) - 1].splice(data_[static_cast<size_t>(QueuePriority::PRIORITY_NUMBERS) - 1].begin(), data_[0]);
}

template<typename T>
bool QueueWithPriority<T>::isEmpty() const noexcept
{
  for (size_t i = 0; i <= static_cast<size_t>(QueuePriority::PRIORITY_NUMBERS) - 1; i++)
  {
    if (!data_[i].empty())
    {
      return false;
    }
  }
  return true;
}

#endif
