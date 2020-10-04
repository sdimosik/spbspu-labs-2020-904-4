#ifndef ACCESS_HPP
#define ACCESS_HPP
#include <cstddef>

template <typename ContainerType>
class IndexAccess
{
public:
  using ElementType = typename ContainerType::reference;
  using IndexType = size_t;
  static ElementType getElement(ContainerType& array, IndexType index);
  static IndexType begin(const ContainerType&);
  static IndexType end(const ContainerType& array);
};

template <typename ContainerType>
typename IndexAccess<ContainerType>::ElementType IndexAccess<ContainerType>::getElement(ContainerType& array, 
    IndexType index)
{
  return array[index];
}

template <typename ContainerType>
typename IndexAccess<ContainerType>::IndexType IndexAccess<ContainerType>::begin(const ContainerType&)
{
  return 0;
}

template <typename ContainerType>
typename IndexAccess<ContainerType>::IndexType IndexAccess<ContainerType>::end(const ContainerType& array)
{
  return array.size();
}

template <typename ContainerType>
class AtAccess
{
public:
  using ElementType = typename ContainerType::reference;
  using IndexType = size_t;
  static ElementType getElement(ContainerType& array, IndexType index);
  static IndexType begin(const ContainerType&);
  static IndexType end(const ContainerType& array);
};

template <typename ContainerType>
typename AtAccess<ContainerType>::ElementType AtAccess<ContainerType>::getElement(ContainerType& array, 
    IndexType index)
{
  return array.at(index);
}

template <typename ContainerType>
typename AtAccess<ContainerType>::IndexType AtAccess<ContainerType>::begin(const ContainerType&)
{
  return 0;
}

template <typename ContainerType>
typename AtAccess<ContainerType>::IndexType AtAccess<ContainerType>::end(const ContainerType& array)
{
  return array.size();
}

template <typename ContainerType>
class IteratorAccess
{
public:
  using ElementType = typename ContainerType::reference;
  using IndexType = typename ContainerType::iterator;
  static ElementType getElement(ContainerType&, IndexType index);
  static IndexType begin(ContainerType& array);
  static IndexType end(ContainerType& array);
};

template <typename ContainerType>
typename IteratorAccess<ContainerType>::ElementType IteratorAccess<ContainerType>::getElement(ContainerType&, 
    IndexType index)
{
  return *index;
}

template <typename ContainerType>
typename IteratorAccess<ContainerType>::IndexType IteratorAccess<ContainerType>::begin(ContainerType& array)
{
  return array.begin();
}

template <typename ContainerType>
typename IteratorAccess<ContainerType>::IndexType IteratorAccess<ContainerType>::end(ContainerType& array)
{
  return array.end();
}

#endif
