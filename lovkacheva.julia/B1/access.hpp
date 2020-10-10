#ifndef ACCESS_HPP
#define ACCESS_HPP

#include <stdexcept>

template<class Container>
struct IndexOperatorAccess
{
  using iterator = size_t;

  static size_t begin(const Container&)
  {
    return 0;
  }

  static size_t end(const Container& container)
  {
    return container.size();
  }

  static size_t next(size_t index)
  {
    return ++index;
  }

  static typename Container::reference get(Container& container, size_t index)
  {
    if (index >= container.size())
    {
      throw std::out_of_range("The container element index is out of range (the container size is "
          + std::to_string(container.size()) + ", index = " + std::to_string(index) + ")");
    }
    return container[index];
  }

};

template<class Container>
struct AtAccess
{
  using iterator = size_t;

  static size_t begin(const Container&)
  {
    return 0;
  }

  static size_t end(const Container& container)
  {
    return container.size();
  }

  static size_t next(size_t index)
  {
    return ++index;
  }

  static typename Container::reference get(Container& container, size_t index)
  {
    return container.at(index);
  }
};

template<class Container>
struct IteratorAccess
{
  using iterator = typename Container::iterator;

  static iterator begin(Container& container)
  {
    return container.begin();
  }

  static iterator end(Container& container)
  {
    return container.end();
  }

  static iterator next(const iterator& iterator)
  {
    return std::next(iterator);
  }

  static typename Container::reference get(Container&, const iterator& iterator)
  {
    return *iterator;
  }

};
#endif
