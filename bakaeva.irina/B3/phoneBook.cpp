#include "phoneBook.hpp"

void PhoneBook::showNote(PhoneBook::iterator it) const
{
  std::cout << it->number_ << " " << it->name_ << "\n";
}

PhoneBook::iterator PhoneBook::next(PhoneBook::iterator it)
{
  return ++it;
}

PhoneBook::iterator PhoneBook::prev(PhoneBook::iterator it)
{
  return --it;
}

PhoneBook::iterator PhoneBook::insertNoteBefore(PhoneBook::iterator it, const PhoneBook::Note &note)
{
  return listOfNotes_.insert(it, note);
}

PhoneBook::iterator PhoneBook::insertNoteAfter(PhoneBook::iterator it, const PhoneBook::Note &note)
{
  return listOfNotes_.insert(++it, note);
}

PhoneBook::iterator PhoneBook::replaceNote(PhoneBook::iterator it, const PhoneBook::Note &note)
{
  *it = note;
  return it;
}

void PhoneBook::pushBack(const PhoneBook::Note &note)
{
  listOfNotes_.push_back(note);
}

PhoneBook::iterator PhoneBook::move(PhoneBook::iterator it, const int steps)
{
  if (steps >= 0)
  {
    int count = steps;
    while (count != 0)
    {
      if (it != prev(listOfNotes_.end()))
      {
        ++it;
        --count;
      }
      else
      {
        it = listOfNotes_.begin();
        --count;
      }
    }
  }

  if (steps < 0)
  {
    int count = steps;
    while (count != 0)
    {
      if (it != listOfNotes_.begin())
      {
        --it;
        ++count;
      }
      else
      {
        it = prev(listOfNotes_.end());
        ++count;
      }
    }
  }
  return it;
}

PhoneBook::iterator PhoneBook::erase(PhoneBook::iterator it)
{
  if (listOfNotes_.empty())
  {
    return listOfNotes_.end();
  }
  return listOfNotes_.erase(it);
}

PhoneBook::iterator PhoneBook::begin() noexcept
{
  return listOfNotes_.begin();
}

PhoneBook::iterator PhoneBook::end() noexcept
{
  return listOfNotes_.end();
}
