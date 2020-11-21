#include "factorial_container.hpp"

factorialContainer::Iterator::Iterator() :
  number_(1),
  value_(1)
{}

factorialContainer::Iterator::Iterator(size_t number) :
  number_(number),
  value_(get_value_from_number(number))
{}

bool factorialContainer::Iterator::operator==(const factorialContainer::Iterator &rhs)
{
  return value_ == rhs.value_;
}

bool factorialContainer::Iterator::operator!=(const factorialContainer::Iterator &rhs)
{
  return value_ != rhs.value_;
}

factorialContainer::Iterator factorialContainer::Iterator::operator++()
{
  if(number_ < max_size_)
  {
    number_++;
    value_ *= number_;

    return *this;
  }
  else
  {
    throw std::invalid_argument(" you are at the last element! \n");
  }
}

factorialContainer::Iterator factorialContainer::Iterator::operator--()
{
  if(number_ > 1)
  {
    value_ /= number_;
    number_--;
    return *this;
  }
  else
  {
    throw std::invalid_argument(" you are at the first element ! \n");
  }
}

factorialContainer::Iterator factorialContainer::Iterator::operator++(int)
{
  Iterator iter = *this;
  ++(*this);
  return iter;
}

factorialContainer::Iterator factorialContainer::Iterator::operator--(int)
{
  Iterator iter = *this;
  --(*this);
  return iter;
}

const unsigned long &factorialContainer::Iterator::operator*() const
{
  return value_;
}

unsigned long factorialContainer::Iterator::get_value_from_number(size_t num) const
{
  if(num <= 1 )
  {
    return 1;
  }
  else
  {
    return num * get_value_from_number(num - 1);
  }
}

factorialContainer::Iterator factorialContainer::begin()
{
  return Iterator();
}

factorialContainer::Iterator factorialContainer::end()
{
  return Iterator(max_size_);
}

