#ifndef ACCESS
#define ACCESS

template <class container> class IndexAccess
{
public:
  static unsigned int begin(container&)
  {
    return 0;
  }
  static unsigned int end(container& collection)
  {
    return collection.size();
  }
  static typename container::reference getElement(container& collection, unsigned int index)
  {
    return collection[index];
  }
};

template <class container> class AtAccess
{
public:
  static unsigned int begin(container&)
  {
    return 0;
  }
  static unsigned int end(container& collection)
  {
    return collection.size();
  }
  static typename container::reference getElement(container& collection, unsigned int index)
  {
    return collection.at(index);
  }

};

template <class container> class IteratorAccess
{
public:
  using iterator_t = typename container::iterator;

  static iterator_t begin(container& collection)
  {
    return collection.begin();
  }

  static iterator_t end(container& collection)
  {
    return collection.end();
  }

  static typename container::reference getElement(container&, iterator_t& iterator)
  {
    return *iterator;
  }
};
#endif // !ACCESS
