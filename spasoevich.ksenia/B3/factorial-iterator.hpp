#ifndef FACTORIAL_ITERATOR_HPP
#define FACTORIAL_ITERATOR_HPP

#include <iterator>

class FactorialContainer
{
public: 
  class IteratorFact : public std::iterator<std::bidirectional_iterator_tag, size_t>
  {
  public:
  IteratorFact();
  IteratorFact(size_t index);
  size_t& operator *();
  size_t* operator ->();
  IteratorFact& operator ++();
  IteratorFact operator ++(int);
  IteratorFact& operator --();
  IteratorFact operator --(int);
  bool operator ==(IteratorFact iter) const;
  bool operator !=(IteratorFact iter) const;
private:
  size_t value;
  size_t pos;
  size_t getValue(size_t val) const;
};
  FactorialContainer() = default;
  IteratorFact begin();
  IteratorFact end();
};
#endif
