#include "factorial.hpp"
#include <stdexcept>

Factorial::IteratorFactorial Factorial::begin()
{
  return Factorial::IteratorFactorial(Factorial::IteratorFactorial::MIN_POSITION);
}

Factorial::IteratorFactorial Factorial::end()
{
  return Factorial::IteratorFactorial(Factorial::IteratorFactorial::MAX_POSITION);
}

Factorial::IteratorFactorial::IteratorFactorial() : 
  position_(1),
  value_(factorial(position_))
{}

Factorial::IteratorFactorial::IteratorFactorial(size_t position) :
  position_(position),
  value_(factorial(position))
{}

bool Factorial::IteratorFactorial::operator==(const IteratorFactorial& rhs) const noexcept
{
  return (position_ == rhs.position_);
}

bool Factorial::IteratorFactorial::operator!=(const IteratorFactorial& rhs) const noexcept
{
  return !(position_ == rhs.position_);
}

const size_t* Factorial::IteratorFactorial::operator->() const noexcept
{
  return &value_;
}

const size_t& Factorial::IteratorFactorial::operator*() const noexcept
{
  return value_;
}

Factorial::IteratorFactorial& Factorial::IteratorFactorial::operator++()
{
  if (position_ < MAX_POSITION)
  {
    ++position_;
    value_ *= position_;
    return *this;
  }
  else
  {
    throw std::out_of_range("Out of range factorial");
  }
}

Factorial::IteratorFactorial& Factorial::IteratorFactorial::operator--()
{
  if (position_ > MIN_POSITION)
  {
    value_ /= position_;
    --position_;
    return *this;
  }
  else
  {
    throw std::out_of_range("Out of range factorial");
  }
}

Factorial::IteratorFactorial Factorial::IteratorFactorial::operator++(int)
{
  Factorial::IteratorFactorial temp = *this;
  ++(*this);
  return temp;
}

Factorial::IteratorFactorial Factorial::IteratorFactorial::operator--(int)
{
  Factorial::IteratorFactorial temp = *this;
  --(*this);
  return temp;
}

size_t Factorial::IteratorFactorial::factorial(const size_t number)
{
  size_t factorial = 1;
  for (size_t i = 2; i <= number; i++)
  {
    factorial *= i;
  }
  return factorial;
}
