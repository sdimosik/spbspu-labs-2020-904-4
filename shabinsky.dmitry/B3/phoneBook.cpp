#include <iostream>
#include "phoneBook.hpp"

PhoneBook::Iterator PhoneBook::insert(const PhoneBook::Note &note, PhoneBook::Iterator it)
{
  return notes_.insert(it, note);
}

PhoneBook::Iterator PhoneBook::replace(PhoneBook::Note &note, PhoneBook::Iterator it)
{
  *it = note;
  return it;
}

PhoneBook::Iterator PhoneBook::removeAt(PhoneBook::Iterator it)
{
  return notes_.erase(it);
}

PhoneBook::Iterator PhoneBook::beginIt()
{
  return notes_.begin();
}

PhoneBook::Iterator PhoneBook::endIt()
{
  return notes_.end();
}

void PhoneBook::pushBack(const PhoneBook::Note &note)
{
  notes_.push_back(note);
}

size_t PhoneBook::size() const
{
  return notes_.size();
}
