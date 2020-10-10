#ifndef B1_RECEIVEELEMENT_HPP
#define B1_RECEIVEELEMENT_HPP

#include <forward_list>
#include <vector>

template<class T>
struct IndexReceive
{
  static size_t begin(const T &)
  {
    return 0;
  }

  static size_t end(const T &container)
  {
    return container.size();
  }

  static typename T::reference element(T &container, size_t i)
  {
    return container[i];
  }
};

template<class T>
struct AtReceive
{
  static size_t begin(const T &)
  {
    return 0;
  }

  static size_t end(const T &container)
  {
    return container.size();
  }

  static typename T::reference element(T &container, size_t i)
  {
    return container.at(i);
  }
};

template<class T>
struct IteratorReceive
{
  static typename T::iterator begin(T& container)
  {
    return container.begin();
  }

  static typename T::iterator end(T& container)
  {
    return container.end();
  }

  static typename T::value_type &element(T &, typename T::iterator it)
  {
    return (*it);
  }
};


#endif
