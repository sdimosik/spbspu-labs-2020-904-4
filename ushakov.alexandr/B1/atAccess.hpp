#ifndef PROGSPBSTUCOPY_ATACCESS_HPP
#define PROGSPBSTUCOPY_ATACCESS_HPP

#include <cstdlib>

template<class container>
class AtAccess
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
    return collection.at(index);
  }

  static size_t next(size_t index)
  {
    return ++index;
  }
};


#endif //PROGSPBSTUCOPY_ATACCESS_HPP
