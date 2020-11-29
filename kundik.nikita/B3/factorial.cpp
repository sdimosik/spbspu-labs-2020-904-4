#include "factorial.hpp"

#define INCORRECT_INDEX "Incorrect index! Index could be from 1 to 11!\n"

Container::Iterator::Iterator() :
  index_(BEGIN_INDEX),
  factorial_(BEGIN_VALUE)
{}

Container::Iterator::Iterator(unsigned int index) :
  index_(index)
{
  if (index < BEGIN_INDEX || index > END_INDEX)
  {
    throw std::out_of_range(INCORRECT_INDEX);
  }

  unsigned int value = BEGIN_VALUE;
  for (unsigned int i = BEGIN_INDEX; i <= index; ++i)
  {
    value *= i;
  }
  factorial_ = value;
}

unsigned int Container::Iterator::operator->() const
{
  return factorial_;
}

unsigned int Container::Iterator::operator*() const
{
  return factorial_;
}

bool Container::Iterator::operator==(const Iterator& rhs) const
{
  return index_ == rhs.index_;
}

bool Container::Iterator::operator!=(const Iterator& rhs) const
{
  return index_ != rhs.index_;
}

Container::Iterator& Container::Iterator::operator++()
{
  if (index_ + 1 > END_INDEX)
  {
    throw std::out_of_range(INCORRECT_INDEX);
  }
  ++index_;
  factorial_ *= index_;
  return *this;
}

Container::Iterator Container::Iterator::operator++(int)
{
  if (index_ + 1 > END_INDEX)
  {
    throw std::out_of_range(INCORRECT_INDEX);
  }
  Iterator temp = *this;
  ++index_;
  factorial_ *= index_;
  return temp;
}

Container::Iterator& Container::Iterator::operator--()
{
  if (index_ - 1 < BEGIN_INDEX)
  {
    throw std::out_of_range(INCORRECT_INDEX);
  }
  factorial_ /= index_;
  --index_;
  return *this;
}

Container::Iterator Container::Iterator::operator--(int)
{
  if (index_ - 1 < BEGIN_INDEX)
  {
    throw std::out_of_range(INCORRECT_INDEX);
  }
  Iterator temp = *this;
  factorial_ /= index_;
  --index_;
  return temp;
}

Container::Iterator Container::begin() const
{
  return Iterator(BEGIN_INDEX);
}

Container::Iterator Container::end() const
{
  return Iterator(END_INDEX);
}
