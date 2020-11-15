#include "phoneBook.hpp"

void PhoneBook::showThisRecord(iterator iter) const
{
  std::cout << iter->number_ << " " << iter->name_ << '\n';
}

void PhoneBook::pushBack(const Records &record)
{
  book_.push_back(record);
}

PhoneBook::iterator PhoneBook::insertBefore(iterator iter, const Records &record)
{
  return book_.insert(iter, record);
}

PhoneBook::iterator PhoneBook::insertAfter(iterator iter, const Records &record)
{
return book_.insert(++iter, record);
}

PhoneBook::iterator PhoneBook::erase(iterator iter)
{
  return book_.erase(iter);
}

PhoneBook::iterator PhoneBook::begin() noexcept
{
  return book_.begin();
}

PhoneBook::iterator PhoneBook::end() noexcept
{
  return book_.end();
}
