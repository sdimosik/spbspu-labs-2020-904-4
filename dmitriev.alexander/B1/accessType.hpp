#ifndef ACCESSTYPE_HPP
#define ACCESSTYPE_HPP

#include <cstddef>

template<class T>
struct AccessByBrackets
{
  static unsigned int begin(const T &)
  {
    return 0;
  }

  static unsigned int end(const T &container)
  {
    return container.size();
  }

  static typename T::reference getElement(T &container, unsigned int i)
  {
    return container[i];
  }
};

template<class T>
struct AccessByAt
{
  static unsigned int begin(const T &)
  {
    return 0;
  }

  static unsigned int end(const T &container)
  {
    return container.size();
  }

  static typename T::reference getElement(T &container, unsigned int i)
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
