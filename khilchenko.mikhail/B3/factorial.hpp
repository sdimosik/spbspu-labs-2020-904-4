#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>

class Factorial
{
public:
  class Iterator : public std::iterator<std::bidirectional_iterator_tag, size_t>
  {
  public:
    static const size_t minIndex = 1;
    static const size_t maxIndex = 11;
    Iterator();
    Iterator(size_t index);
    size_t& operator*();
    size_t* operator->();
    Iterator operator++();
    Iterator operator++(int);
    Iterator operator--();
    Iterator operator--(int);
    bool operator==(Iterator& it) const;
    bool operator!=(Iterator& it) const;
  private:
    size_t value_;
    size_t index_;
    static size_t getFactorial(size_t index);
  };

  Factorial::Iterator begin();
  Factorial::Iterator end();
};

#endif
