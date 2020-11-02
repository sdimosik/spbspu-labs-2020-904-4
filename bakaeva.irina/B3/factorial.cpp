#include "factorial.hpp"

Factorial::Iterator Factorial::begin()
{
  return {Iterator::MIN_ORDER};
}

Factorial::Iterator Factorial::end()
{
  return {Iterator::MAX_ORDER};
}

Factorial::Iterator::Iterator() :
        order_(1),
        value_(1)
{}

Factorial::Iterator::Iterator(size_t order) :
        order_(order),
        value_(getFactorial(order))
{
  if ((order < MIN_ORDER) || (order > MAX_ORDER))
  {
    throw std::out_of_range("Order is out of range!");
  }
}

const size_t &Factorial::Iterator::operator*() const noexcept
{
  return value_;
}

const size_t *Factorial::Iterator::operator->() const noexcept
{
  return &value_;
}

Factorial::Iterator &Factorial::Iterator::operator++()
{
  if (order_ > MAX_ORDER)
  {
    throw std::out_of_range("Order must be less than 11!");
  }

  ++order_;
  value_ *= order_;
  return *this;
}

Factorial::Iterator Factorial::Iterator::operator++(int)
{
  const Iterator temp = *this;
  this->operator++();

  return temp;
}

Factorial::Iterator &Factorial::Iterator::operator--()
{
  if (order_ <= MIN_ORDER)
  {
    throw std::out_of_range("Order must be more than 0!");
  }

  value_ /= order_;
  --order_;
  return *this;
}

Factorial::Iterator Factorial::Iterator::operator--(int)
{
  const Iterator temp = *this;
  this->operator--();
  return temp;
}

bool Factorial::Iterator::operator==(const Iterator &rhs) const
{
  return value_ == rhs.value_;
}

bool Factorial::Iterator::operator!=(const Iterator &rhs) const
{
  return value_ != rhs.value_;
}

size_t Factorial::Iterator::getFactorial(size_t index) const
{
  size_t factorial = 1;
  for (size_t i = 1; i < index + 1; i++)
  {
    factorial *= i;
  }
  return factorial;
}
