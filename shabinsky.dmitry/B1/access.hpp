#ifndef B1_ACCESS_HPP
#define B1_ACCESS_HPP

template<class Container>
class IndexAccess
{
public:
  static unsigned int begin(Container &)
  {
    return 0;
  }
  
  static unsigned int end(Container &collection)
  {
    return collection.size();
  }
  
  static typename Container::reference getElement(Container &collection, unsigned int index)
  {
    return collection[index];
  }
};

template<class Container>
class AtAccess
{
public:
  static unsigned int begin(Container &)
  {
    return 0;
  }
  
  static unsigned int end(Container &collection)
  {
    return collection.size();
  }
  
  static typename Container::reference getElement(Container &collection, unsigned int index)
  {
    return collection.at(index);
  }
  
};

template<class Container>
class IteratorAccess
{
public:
  using iterator_t = typename Container::iterator;
  
  static iterator_t begin(Container &collection)
  {
    return collection.begin();
  }
  
  static iterator_t end(Container &collection)
  {
    return collection.end();
  }
  
  static typename Container::reference getElement(Container &, iterator_t &iterator)
  {
    return *iterator;
  }
};

#endif //B1_ACCESS_HPP
