//
// Created by sdimosik on 29.10.2020.
//

#include "factorial.hpp"

Factorial::Iterator::Iterator() :
  position_(MIN_POS),
  value_(MIN_POS)
{}

Factorial::Iterator::Iterator(size_t position) :
  position_(position),
  value_(Factorial::Iterator::getFactorial(position))
{
  if ((position < MIN_POS) || (position > MAX_POS))
  {
    throw std::out_of_range("Position is out of range!\n");
  }
}

size_t &Factorial::Iterator::operator*()
{
  return value_;
}

size_t *Factorial::Iterator::operator->()
{
  return &value_;
}

Factorial::Iterator &Factorial::Iterator::operator++()
{
  if (position_ > MAX_POS)
  {
    throw std::out_of_range(&"Position must be less than "[MAX_POS]);
  }
  
  position_++;
  value_ *= position_;
  return *this;
}

const Factorial::Iterator Factorial::Iterator::operator++(int)
{
  const Factorial::Iterator tempIter = *this;
  this->operator++();
  
  return tempIter;
}

Factorial::Iterator &Factorial::Iterator::operator--()
{
  if (position_ <= MIN_POS)
  {
    throw std::out_of_range("Position must be more than 0!\n");
  }
  
  value_ /= position_;
  position_--;
  
  return *this;
}

const Factorial::Iterator Factorial::Iterator::operator--(int)
{
  const Factorial::Iterator tempIter = *this;
  this->operator--();
  
  return tempIter;
}

bool Factorial::Iterator::operator==(const Factorial::Iterator &rhs) const
{
  return value_ == rhs.value_;
}

bool Factorial::Iterator::operator!=(const Factorial::Iterator &rhs) const
{
  return value_ != rhs.value_;
}

size_t Factorial::Iterator::getFactorial(size_t number)
{
  size_t factorial = MIN_POS;
  for (size_t i = MIN_POS; i <= number; i++)
  {
    factorial *= i;
  }
  
  return factorial;
}

Factorial::Iterator Factorial::begin()
{
  return {Factorial::Iterator::MIN_POS};
}

Factorial::Iterator Factorial::end()
{
  return {Factorial::Iterator::MAX_POS};
}
