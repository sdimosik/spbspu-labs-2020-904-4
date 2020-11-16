#include "factorial.hpp"

Factorial::Iterator::Iterator() :
  argument_(MIN_ARGUMENT), factorial_(MIN_ARGUMENT)
{}

Factorial::Iterator::Iterator(const size_t argument) :
  argument_(argument), factorial_(getFactorial(argument))
{
  if ((argument < MIN_ARGUMENT) || (argument > MAX_ARGUMENT))
  {
    throw std::invalid_argument("Invalid argument for iterator");
  }
}

size_t& Factorial::Iterator::operator*()
{
  return factorial_;
}

size_t* Factorial::Iterator::operator->()
{
  return &factorial_;
}

Factorial::Iterator Factorial::Iterator::operator++()
{
  if (argument_ > MAX_ARGUMENT)
  {
    throw std::out_of_range("Agrument of iterator out of range");
  }
  ++argument_;
  factorial_ *= argument_;
  return *this;
}

Factorial::Iterator Factorial::Iterator::operator++(int)
{
  if (argument_ > MAX_ARGUMENT)
  {
    throw std::out_of_range("Agrument of iterator out of range");
  }
  Iterator temp(*this);
  ++argument_;
  factorial_ *= argument_;
  return temp;
}

Factorial::Iterator Factorial::Iterator::operator--()
{
  if (argument_ <= MIN_ARGUMENT)
  {
    throw std::out_of_range("Agrument of iterator out of range");
  }
  factorial_ /= argument_;
  --argument_;
  return *this;
}

Factorial::Iterator Factorial::Iterator::operator--(int)
{
  if (argument_ <= MIN_ARGUMENT)
  {
    throw std::out_of_range("Agrument of iterator out of range");
  }
  Iterator temp(*this);
  factorial_ /= argument_;
  --argument_;
  return temp;
}

bool Factorial::Iterator::operator==(const Iterator& iterator)
{
  return argument_ == iterator.argument_;
}

bool Factorial::Iterator::operator!=(const Iterator& iterator)
{
  return argument_ != iterator.argument_;
}

size_t Factorial::Iterator::getFactorial(size_t argument) const
{
  size_t temp = 1u;
  for (size_t i = 2; i <= argument; ++i)
  {
    temp *= i;
  }
  return temp;
}

Factorial::Iterator Factorial::Factorial::begin()
{
  return Iterator();
}

Factorial::Iterator Factorial::Factorial::end()
{
  return Iterator(Iterator::MAX_ARGUMENT);
}
