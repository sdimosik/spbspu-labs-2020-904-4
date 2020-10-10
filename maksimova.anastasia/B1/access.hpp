#ifndef ACCESS_HPP
#define ACCESS_HPP

#include <iostream>

template <class container>
class index_access
{
public:
  static size_t begin(const container &)
  {
    return 0;
  }
  static size_t end(const container & collection)
  {
    return collection.size();
  }
  static typename container::reference get_element(container & collection, size_t index)
  {
    return collection[index];
  }
  static size_t next(size_t index)
  {
    return index + 1;
  }
};

template <class container>
class at_access
{
public:
  static size_t begin(const container &)
  {
    return 0;
  }
  static size_t end(const container & collection)
  {
    return collection.size();
  }
  static typename container::reference get_element(container & collection, size_t index)
  {
    return collection.at(index);
  }
  static size_t next(size_t index)
  {
    return index + 1;
  }
};

template <class container>
class iter_access
{
public:
  using iter = typename container::iterator;
  static iter begin(container & collection)
  {
    return collection.begin();
  }
  static iter end(container & collection)
  {
    return collection.end();
  }
  static typename container::reference get_element(container &, iter & i)
  {
    return *i;
  }
  static size_t next(iter &i)
  {
    return std::next(i);
  }
};

#endif
