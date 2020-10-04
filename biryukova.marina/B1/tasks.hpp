#ifndef TASKS_HPP
#define TASKS_HPP
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <functional>

void task1(const std::string& order);
void task2(const std::string& data);
void task3();
void task4(const std::string& order, const std::string& size);
void fillRandom(double* array, int size);

template <typename ContainerType>
void print(ContainerType& array, const char* separator)
{
  typename ContainerType::iterator iter = array.begin();
  while (iter != array.end())
  {
    std::cout << *iter << separator;
    iter++;
  }
  std::cout << '\n';
}

template <typename Type>
std::function<bool(const Type&, const Type&)> getComparator(const std::string& order)
{
  if (order == "ascending")
  {
    return std::less<const Type>();
  }
  else
  {
    return std::greater<const Type>();
  }
}

template <template <typename> class AccessType, typename ContainerType>
void selectionSort(ContainerType& array, std::function<bool(typename ContainerType::const_reference, 
    typename ContainerType::const_reference)> comparator)
{
  for (auto i = AccessType<ContainerType>::begin(array); i != AccessType<ContainerType>::end(array); i++)
  {
    auto index = i;
    for (auto j = i; j != AccessType<ContainerType>::end(array); j++) 
    {
      if (j == i)
      {
        continue;
      }
      if (comparator(AccessType<ContainerType>::getElement(array, j), 
          AccessType<ContainerType>::getElement(array, index)))
      {
        index = j;
      }
    }
    if (index != i)
    {
      std::swap(AccessType<ContainerType>::getElement(array, i), AccessType<ContainerType>::getElement(array, index));
    }
  }
}
 
#endif
