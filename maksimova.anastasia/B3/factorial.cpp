#include "factorial.hpp"

Factorial::Iterator Factorial::begin()
{
  return {Iterator::MIN_POS};
}

Factorial::Iterator Factorial::end()
{
  return {Iterator::MAX_POS};
}

Factorial::Iterator::Iterator() :
  pos_(MIN_POS),
  value_(MIN_POS)
{}

Factorial::Iterator::Iterator(size_t pos) :
  pos_(pos),
  value_(factorial(pos))
{
  if ((pos < MIN_POS) || (pos > MAX_POS))
  {
    throw std::invalid_argument("Invalid argument: " + std::to_string(pos));
  }
}

bool Factorial::Iterator::operator==(const Iterator &rhs) const noexcept
{
  return pos_ == rhs.pos_;
}

bool Factorial::Iterator::operator!=(const Iterator &rhs) const noexcept
{
  return pos_ != rhs.pos_;
}

Factorial::Iterator & Factorial::Iterator::operator++()
{
  if (pos_ >= MAX_POS)
  {
    throw std::invalid_argument("Invalid argument: " + std::to_string(pos_));
  }
  ++pos_;
  value_ *= pos_;
  return *this;
}

Factorial::Iterator Factorial::Iterator::operator++(int)
{
  Iterator temp = *this;
  ++(*this);
  return temp;
}

Factorial::Iterator & Factorial::Iterator::operator--()
{
  if(pos_ <= MIN_POS)
  {
    throw std::invalid_argument("Invalid argument: " + std::to_string(pos_));
  }
  value_ /= pos_;
  --pos_;
  return *this;
}

Factorial::Iterator Factorial::Iterator::operator--(int)
{
  Iterator temp = *this;
  --(*this);
  return temp;
}

const size_t & Factorial::Iterator::operator*() const noexcept
{
  return value_;
}

const size_t * Factorial::Iterator::operator->() const noexcept
{
  return &value_;
}

size_t Factorial::Iterator::factorial(const size_t number)
{
  size_t factorial = 1;
  for (size_t i = 1; i <= number; ++i)
  {
    factorial *= i;
  }
  return factorial;
}



