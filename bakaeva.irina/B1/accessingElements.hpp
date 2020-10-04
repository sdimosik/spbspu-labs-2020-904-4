#ifndef B1_ACCESSINGELEMENTS_HPP
#define B1_ACCESSINGELEMENTS_HPP

#include <cstddef>

template<class T>
struct AccessByBrackets
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
struct AccessByAt
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
struct AccessByIterator
{
  static auto begin(T &container) -> decltype(container.begin())
  {
    return container.begin();
  }

  static auto end(T &container) -> decltype(container.end())
  {
    return container.end();
  }

  static typename T::value_type &getElement(T &, typename T::iterator it)
  {
    return (*it);
  }
};

#endif
