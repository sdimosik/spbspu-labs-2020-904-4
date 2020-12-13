#ifndef SPBSPU_LABS_2020_904_4_ACCESS_HPP
#define SPBSPU_LABS_2020_904_4_ACCESS_HPP

#include <cstddef>

template<class T>
struct IndexAccess
{
  static size_t begin(const T &)
  {
    return 0;
  }

  static size_t end(const T &container)
  {
    return container.size();
  }

  static typename T::reference getElement(T &container, size_t i)
  {
    return container[i];
  }

};

template<class T>
struct AtAccess
{
  static size_t begin(const T &)
  {
    return 0;
  }

  static size_t end(const T &container)
  {
    return container.size();
  }

  static typename T::reference getElement(T &container, size_t i)
  {
    return container.at(i);
  }

};

template<class T>
struct IteratorAccess
{
  using iterator_t = typename T::iterator;

  static iterator_t begin(T &collection)
  {
    return collection.begin();
  }

  static iterator_t end(T &collection)
  {
    return collection.end();
  }

  static typename T::reference getElement(T &, iterator_t i)
  {
    return *i;
  }

};

#endif
