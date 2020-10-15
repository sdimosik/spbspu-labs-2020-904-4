#ifndef B2_QUEUEWITHPRIORITY_HPP
#define B2_QUEUEWITHPRIORITY_HPP

#include <iostream>
#include<list>

template<typename T>
class QueueWithPriority
{
public:
  typedef enum
  {
    LOW_PRIORITY,
    NORMAL_PRIORITY,
    HIGH_PRIORITY,
    WRONG_PRIORITY
  } ElementPriority;

  void put_element_to_queue(const T& element, ElementPriority priority);
  void get_element_from_queue(T& element);
  void accelerate();
  bool is_empty() const noexcept;
private:
  std::list<T> queue_list[3];
};

template<typename T>
void QueueWithPriority<T>::put_element_to_queue(const T& element, ElementPriority priority)
{
  queue_list[priority].push_back(element);
}

template<typename T>
void QueueWithPriority<T>::get_element_from_queue(T& element)
{
  if(this->is_empty())
  {
    throw std::runtime_error("can't get element from empty queue! \n");
  }
  else
  {
    for (int priority = HIGH_PRIORITY; priority >= 0; priority--)
    {
      if (!queue_list[priority].empty())
      {
        element = queue_list[priority].front();
        queue_list[priority].pop_front();
        break;
      }
    }
  }
}

template<typename T>
void QueueWithPriority<T>::accelerate()
{
   queue_list[HIGH_PRIORITY].splice(queue_list[HIGH_PRIORITY].end(), queue_list[LOW_PRIORITY]);
}

template<typename T>
bool QueueWithPriority<T>::is_empty() const noexcept
{
  return (queue_list[HIGH_PRIORITY].empty() && queue_list[NORMAL_PRIORITY].empty() && queue_list[LOW_PRIORITY].empty());
}

std::istream& operator >> (std::istream& input, QueueWithPriority<std::string>::ElementPriority& elem)
{
  std::string priority;
  input >> priority;
  if (priority == "low")
  {
    elem =  QueueWithPriority<std::string>::ElementPriority::LOW_PRIORITY;
  }
  else if (priority == "normal")
  {
    elem =  QueueWithPriority<std::string>::NORMAL_PRIORITY;
  }
  else if (priority == "high")
  {
    elem =  QueueWithPriority<std::string>::HIGH_PRIORITY;
  }
  else
  {
    elem =  QueueWithPriority<std::string>::WRONG_PRIORITY;
  }
  return input;
}

#endif //B2_QUEUEWITHPRIORITY_HPP
