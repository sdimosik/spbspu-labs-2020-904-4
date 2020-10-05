#ifndef ACCESS_HPP
#define ACCESS_HPP

#include <iterator>

template <typename T>
struct accessUsingOperator 
{
  static size_t begin(const T&)
  {
    return 0;
  }

  static size_t end(const T& collection)
  {
    return collection.size();
  }

  static typename T::reference element(T& collection, size_t i)
  {
    return collection[i];
  }

  static size_t next(size_t i)
  {
    return i + 1;
  }
};

template <typename T>
struct accessUsingAt 
{
    
  static size_t begin(const T&)
  {
    return 0;
  }

  static size_t end(const T& collection)
  {
    return collection.size();
  }

  static typename T::reference element(T& collection, size_t i)
  {
    return collection.at(i);
  }

  static size_t next(size_t i)
  {
    return i + 1;
  }
};

template <typename T>
struct accessUsingIterator
{
  typedef typename T::iterator index;

  static index begin(T& collection)
  {
    return collection.begin();
  }

  static index end(T& collection)
  {
    return collection.end();
  }

  static typename T::reference element(T&, index& iterator)
  {
    return *iterator;
  }

  static index next(index& iterator)
  {
    return std::next(iterator);
  }
};

#endif

