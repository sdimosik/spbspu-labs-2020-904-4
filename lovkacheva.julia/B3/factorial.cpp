#include "factorial.hpp"

const size_t MIN_VALUE = 1;
const size_t MAX_INDEX = 10;
const size_t MIN_INDEX = 1;

lovkacheva::Factorial::Iterator lovkacheva::Factorial::begin()
{
  return lovkacheva::Factorial::Iterator(MIN_VALUE, MIN_INDEX);
}

lovkacheva::Factorial::Iterator lovkacheva::Factorial::end()
{
  return lovkacheva::Factorial::Iterator();
}

lovkacheva::Factorial::Iterator::Iterator():
  index_(0),
  value_(0)
{}

lovkacheva::Factorial::Iterator::Iterator(size_t value, size_t index):
  index_(index),
  value_(value)
{}

size_t &lovkacheva::Factorial::Iterator::operator*()
{
  return value_;
}

size_t *lovkacheva::Factorial::Iterator::operator->()
{
  return &value_;
}

lovkacheva::Factorial::Iterator lovkacheva::Factorial::Iterator::operator++(int)
{
  Iterator temp = *this;
  ++*this;
  return temp;
}

lovkacheva::Factorial::Iterator lovkacheva::Factorial::Iterator::operator++()
{
  if (value_ == 0)
  {
    throw std::out_of_range("Factorial iterator is out of range");
  }
  if (index_ == MAX_INDEX)
  {
    value_ = 0;
    index_ = 0;
  }
  else
  {
    ++index_;
    value_ *= index_;
  }
  return *this;
}

lovkacheva::Factorial::Iterator lovkacheva::Factorial::Iterator::operator--(int)
{
  Iterator temp = *this;
  --*this;
  return temp;
}

lovkacheva::Factorial::Iterator lovkacheva::Factorial::Iterator::operator--()
{
  if (index_ == MIN_INDEX)
  {
    throw std::out_of_range("Factorial iterator is out of range");
  }
  if (value_ == 0)
  {
    value_ = MIN_VALUE;
    index_ = MIN_INDEX;
    while (index_ < MAX_INDEX)
    {
      ++*this;
    }
  }
  else
  {
    value_ /= index_;
    --index_;
  }
  return *this;
}

bool lovkacheva::Factorial::Iterator::operator==(const Iterator &rhs)
{
  return value_ == rhs.value_;
}

bool lovkacheva::Factorial::Iterator::operator!=(const Iterator &rhs)
{
  return !(*this == rhs);
}
