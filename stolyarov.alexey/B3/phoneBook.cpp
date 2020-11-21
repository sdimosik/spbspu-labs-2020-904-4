#include "phoneBook.hpp"

void PhoneBook::show(iterator it) const
{
  std::cout << it->number_ << " " << it->name_ << "\n";
}

void PhoneBook::pushBack(const PhoneBookNote& note)
{
  noteList_.push_back(note);
}

PhoneBook::iterator PhoneBook::deleteBookmark(iterator it)
{
  if (noteList_.empty())
  {
    return noteList_.end();
  }
  return noteList_.erase(it);
}

PhoneBook::iterator PhoneBook::insertAfter(PhoneBook::iterator it, const PhoneBook::PhoneBookNote& note)
{
  return noteList_.insert(++it, note);
}

PhoneBook::iterator PhoneBook::insertBefore(PhoneBook::iterator it, const PhoneBook::PhoneBookNote& note)
{
  return noteList_.insert(it, note);
}

PhoneBook::iterator PhoneBook::begin() noexcept
{
  return noteList_.begin();
}

PhoneBook::iterator PhoneBook::end() noexcept
{
  return noteList_.end();
}
