#include "telephone-book.hpp"

TelephoneBook::Iterator TelephoneBook::insertBefore(Note& note, Iterator iterator)
{
  return container_.insert(iterator, note);
}

TelephoneBook::Iterator TelephoneBook::insertAfter(Note& note, Iterator iterator)
{
  return container_.insert(++iterator, note);
}

TelephoneBook::Iterator TelephoneBook::replace(Note& note, Iterator iterator)
{
  iterator = container_.erase(iterator);
  return container_.insert(iterator, note);
}

void TelephoneBook::insertBack(Note& note)
{
  container_.push_back(note);
}

TelephoneBook::Iterator TelephoneBook::deleteNote(Iterator iterator)
{
  return (iterator != container_.end() ? container_.erase(iterator) : container_.end());
}

bool TelephoneBook::isEmpty() const noexcept
{
  return container_.empty();
}

TelephoneBook::Iterator TelephoneBook::begin()
{
  return container_.begin();
}

TelephoneBook::Iterator TelephoneBook::end()
{
  return container_.end();
}
