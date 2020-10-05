#ifndef BUBBLE_SORT_HPP
#define BUBBLE_SORT_HPP

#include "access.hpp"

namespace lovkacheva
{
  template<class Container, class Access, class Compare>
  void bubbleSort(Container& container, Compare compare = Compare())
  {
    if (container.empty())
    {
      return;
    }
    using It = typename Access::iterator;
    const It begin = Access::begin(container);
    const It end = Access::end(container);
    const It second = Access::next(begin);

    It iPrevious = end;
    for (It i = end; i != second; i = iPrevious)
    {
      It jNext = second;
      for (It j = begin; jNext != i; j = Access::next(j), jNext = Access::next(jNext))
      {
        if (compare(Access::get(container, j), Access::get(container, jNext)))
        {
          std::swap(Access::get(container, j), Access::get(container, jNext));
        }
        if (Access::next(jNext) == i)
        {
          iPrevious = jNext;
        }
      }
    }
  };
}
#endif
