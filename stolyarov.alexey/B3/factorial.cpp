#include "factorial.hpp"
#include <stdexcept>

Factorial::Iterator::Iterator() :
  value_(1),
  index_(1)
{}

Factorial::Iterator::Iterator(size_t index) :
  value_(getFactorial(index)),
  index_(index)
{
  if (index < MIN_INDEX || index > MAX_INDEX)
  {
    throw std::out_of_range("Invalid index!");
  }
}

const size_t& Factorial::Iterator::operator*() const noexcept
{
  return value_;
}

const size_t* Factorial::Iterator::operator->() const noexcept
{
  return &value_;
}

Factorial::Iterator& Factorial::Iterator::operator++()
{
  if (index_ > MAX_INDEX)
  {
    throw std::out_of_range("Index cannot be less than 11!");
  }

  ++index_;
  value_ *= index_;
  return *this;
}

Factorial::Iterator Factorial::Iterator::operator++(int)
{
  const Iterator temp = *this;
  this->operator++();

  return temp;
}

Factorial::Iterator& Factorial::Iterator::operator--()
{
  if (index_ <= MIN_INDEX)
  {
    throw std::out_of_range("Index cannot be less than 0!");
  }
  value_ /= index_;
  --index_;
  return *this;
}

Factorial::Iterator Factorial::Iterator::operator--(int)
{
  const Iterator temp = *this;
  this->operator--();
  return temp;
}

bool Factorial::Iterator::operator==(const Iterator& it) const
{
  return value_ == it.value_;
}

bool Factorial::Iterator::operator!=(const Iterator& it) const
{
  return value_ != it.value_;
}

size_t Factorial::Iterator::getFactorial(size_t index) const
{
  size_t temp = 1;
  for (size_t i = 1; i <= index; i++)
  {
    temp *= i;
  }
  return temp;
}

Factorial::Iterator Factorial::begin()
{
  return { Iterator::MIN_INDEX };
}

Factorial::Iterator Factorial::end()
{
  return { Iterator::MAX_INDEX };
}
