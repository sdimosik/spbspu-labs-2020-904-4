#include <iostream>
#include "phoneBook.hpp"

void PhoneBook::show(PhoneBook::Iterator it)
{
  if (it != notes_.end())
  {
    std::cout << it->number_ + " " + it->name_ + "\n";
  }
}

PhoneBook::Iterator PhoneBook::next(PhoneBook::Iterator it)
{
  if (it != notes_.end())
  {
    return std::next(it);
  }
  return notes_.end();
}

PhoneBook::Iterator PhoneBook::prev(PhoneBook::Iterator it)
{
  if (it != notes_.end())
  {
    return std::prev(it);
  }
  return notes_.begin();
}

PhoneBook::Iterator PhoneBook::insert(const PhoneBook::Note &note, PhoneBook::InsertType type, PhoneBook::Iterator it)
{
  if (type == InsertType::BEFORE)
  {
    return notes_.insert(it, note);
  }
  else
  {
    return notes_.insert(++it, note);
  }
}

PhoneBook::Iterator PhoneBook::replace(PhoneBook::Note &note, PhoneBook::Iterator it)
{
  *it = note;
  return it;
}

PhoneBook::Iterator PhoneBook::move(int step, PhoneBook::Iterator it)
{
  int counter = 0;
  if (step > 0)
  {
    while (counter != step && it != std::prev(notes_.end()))
    {
      it = std::next(it);
      ++counter;
    }
  }
  else if (step < 0)
  {
    while (counter != step && it != notes_.begin())
    {
      it = std::prev(it);
      --counter;
    }
  }
  return it;
}

PhoneBook::Iterator PhoneBook::remove(PhoneBook::Iterator it)
{
  return notes_.erase(it);
}

PhoneBook::Iterator PhoneBook::begin()
{
  return notes_.begin();
}

PhoneBook::Iterator PhoneBook::end()
{
  return notes_.end();
}

void PhoneBook::push_back(const PhoneBook::Note &note)
{
  notes_.push_back(note);
}

size_t PhoneBook::size() const
{
  return notes_.size();
}
