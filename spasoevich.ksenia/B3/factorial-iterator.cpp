#include <stdexcept>
#include "factorial-iterator.hpp"

const int MIN = 1;
const int MAX = 10;

FactorialContainer::IteratorFact::IteratorFact() :
  value(1),
  pos(1)
{}

FactorialContainer::IteratorFact::IteratorFact(size_t index) :
  value(getValue(index)),
  pos(index)
{
  if ((index < MIN) || (index > MAX + 1))
  {
    throw std::out_of_range("Index is out of range");
  }
}

size_t FactorialContainer::IteratorFact::getValue(size_t val) const
{
  if (val <= MIN)
  {
    return 1;
  }

  return val * getValue(val - 1);
}


size_t& FactorialContainer::IteratorFact::operator*()
{
  return value;
}

size_t* FactorialContainer::IteratorFact::operator->()
{
  return &value;
}

FactorialContainer::IteratorFact& FactorialContainer::IteratorFact::operator++()
{
  if (pos > MAX)
  {
    throw std::out_of_range("Index is out of range");
  }

  ++pos;
  value *= pos;
  return *this;
}

FactorialContainer::IteratorFact FactorialContainer::IteratorFact::operator++(int)
{
  IteratorFact tempIterator = *this;
  ++(*this);
  return tempIterator;
}

FactorialContainer::IteratorFact& FactorialContainer::IteratorFact::operator--()
{
  if (pos <= MIN)
  {
    throw std::out_of_range("Index is out of range");
  }

  value= value/pos;
  --pos;
  return *this;
}

FactorialContainer::IteratorFact FactorialContainer::IteratorFact::operator--(int)
{
  IteratorFact tempIterator = *this;
  --(*this);
  return tempIterator;
}

bool FactorialContainer::IteratorFact::operator ==(IteratorFact iter) const
{
  return (value == iter.value) && (pos == iter.pos);
}

bool FactorialContainer::IteratorFact::operator !=(IteratorFact iter) const
{
  return !(*this == iter);
}

FactorialContainer::IteratorFact FactorialContainer::begin()
{
  return IteratorFact(MIN);
}

FactorialContainer::IteratorFact FactorialContainer::end()
{
  return IteratorFact(MAX + 1);
}
