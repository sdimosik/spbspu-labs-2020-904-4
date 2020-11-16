#include "factorial.hpp"

#include <stdexcept>
#include <iostream>

Factorial::Iterator Factorial::begin()
{
  return Iterator(Iterator::minIndex);
}

Factorial::Iterator Factorial::end()
{
  return Iterator(Iterator::maxIndex);
}

Factorial::Iterator::Iterator():
  value_(minIndex),
  index_(minIndex)
{}

Factorial::Iterator::Iterator(size_t index):
  value_(getFactorial(index)),
  index_(index)
{
  if(index < minIndex || index > maxIndex)
  {
    throw std::invalid_argument("Invalid index: " + std::to_string(index));
  }
}

size_t& Factorial::Iterator::operator*()
{
  return value_;
}

size_t* Factorial::Iterator::operator->()
{
  return &value_;
}

Factorial::Iterator Factorial::Iterator::operator++()
{
  if(index_ > maxIndex)
  {
    throw std::out_of_range("Iterator out of range");
  }
  index_++;
  value_ *= index_;
  return *this;
}

Factorial::Iterator Factorial::Iterator::operator++(int)
{
  Iterator temp = *this;
  this->operator++();
  return temp;
}

Factorial::Iterator Factorial::Iterator::operator--()
{
  if(index_ <= minIndex)
  {
    throw std::out_of_range("Iterator out of range");
  }
  value_ /= index_;
  index_--;
  return *this;
}

Factorial::Iterator Factorial::Iterator::operator--(int)
{
  Iterator temp = *this;
  this->operator--();
  return temp;
}

bool Factorial::Iterator::operator==(Iterator& it) const
{
  return index_ == it.index_;
}

bool Factorial::Iterator::operator!=(Iterator& it) const
{
  return index_ != it.index_;
}

size_t Factorial::Iterator::getFactorial(size_t index)
{
  size_t factorial = 1;
  for(size_t i = 1; i <= index; i++)
  {
    factorial *= i;
  }
  return factorial;
}
