#ifndef PROGSPBSTUCOPY_INDEXACCESS_HPP
#define PROGSPBSTUCOPY_INDEXACCESS_HPP

#include <cstdlib>

template<class container>
class IndexAccess
{
public:
  static size_t begin(const container&)
  {
    return 0;
  }

  static size_t end(const container& collection)
  {
    return collection.size();
  }

  static typename container::reference element(container& collection, size_t index)
  {
    return collection[index];
  }

  static size_t next(size_t index)
  {
    return ++index;
  }
};

#endif //PROGSPBSTUCOPY_INDEXACCESS_HPP
