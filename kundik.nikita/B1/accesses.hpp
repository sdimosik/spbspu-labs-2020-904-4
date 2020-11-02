#ifndef LABS_ACCESSES_HPP
#define LABS_ACCESSES_HPP

namespace detail
{
  template<typename Container>
  struct AccessByIndex
  {
    typedef typename Container::value_type value_t;
    typedef typename Container::size_type index_t;

    static index_t getBegin(Container&)
    {
      return 0;
    }

    static index_t getEnd(Container& container)
    {
      return container.size();
    }

    static value_t& getElement(Container& container, index_t index)
    {
      return container[index];
    }
  };

  template<typename Container>
  struct AccessByAt
  {
    typedef typename Container::value_type value_t;
    typedef typename Container::size_type index_t;

    static index_t getBegin(Container&)
    {
      return 0;
    }

    static index_t getEnd(Container& container)
    {
      return container.size();
    }

    static value_t& getElement(Container& container, index_t index)
    {
      return container.at(index);
    }
  };

  template<typename Container>
  struct AccessByIterator
  {
    typedef typename Container::value_type value_t;
    typedef typename Container::iterator index_t;

    static index_t getBegin(Container& container)
    {
      return container.begin();
    }

    static index_t getEnd(Container& container)
    {
      return container.end();
    }

    static value_t& getElement(Container&, index_t index)
    {
      return *index;
    }
  };
}
#endif
