#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <vector>

template<class container>
class Iterator
{
public:
  using iterator = typename container::iterator;

  static iterator begin(container& collection)
  {
    return collection.begin();
  }

  static iterator end(container& collection)
  {
    return collection.end();
  }

  static typename container::reference element(container&, iterator& iterator)
  {
    return *iterator;
  }

  static iterator next(iterator& iterator)
  {
    return std::next(iterator);
  }
};

#endif
