#include "phoneBook.hpp"

PhoneBook::iterator PhoneBook::insertNote(const PhoneBook::iterator it, const PhoneBook::Note &note)
{
  return noteList_.insert(it, note);
}

PhoneBook::iterator PhoneBook::removeAt(const PhoneBook::iterator it)
{
  return noteList_.erase(it);
}

PhoneBook::iterator PhoneBook::beginIter()
{
  return noteList_.begin();
}

PhoneBook::iterator PhoneBook::endIter()
{
  return noteList_.end();
}

void PhoneBook::pushBack(const PhoneBook::Note &note)
{
  noteList_.push_back(note);
}

int PhoneBook::size() const
{
  return noteList_.size();
}
