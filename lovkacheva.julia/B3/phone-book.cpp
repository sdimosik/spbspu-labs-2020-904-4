#include "phone-book.hpp"
#include <iostream>
#include <iterator>
#include <stdexcept>

using iterator = typename lovkacheva::PhoneBook::iterator;

void lovkacheva::PhoneBook::show(const iterator& it, std::ostream &out) const
{
  if (it == contents_.end())
  {
    throw std::invalid_argument("Invalid iterator");
  }
  out << it->number_ <<  ' ' << it->name_ << '\n';
}

iterator lovkacheva::PhoneBook::insertBefore(const iterator& it, std::string name, std::string number)
{
  return contents_.insert(it, {name, number});
}

iterator lovkacheva::PhoneBook::insertAfter(const iterator& it, std::string name, std::string number)
{
  if (empty())
  {
    return contents_.insert(contents_.begin(), {name, number});
  }
  return contents_.insert(std::next(it), {name, number});
}

iterator lovkacheva::PhoneBook::insertBack(std::string name, std::string number)
{
  return contents_.insert(contents_.end(), {name, number});
}

void lovkacheva::PhoneBook::erase(iterator& it)
{
  it = contents_.erase(it);
}

iterator lovkacheva::PhoneBook::begin()
{
  return contents_.begin();
}

iterator lovkacheva::PhoneBook::end()
{
  return contents_.end();
}

bool lovkacheva::PhoneBook::empty() const
{
  return contents_.empty();
}

std::list<lovkacheva::PhoneBook::entry_t>::size_type lovkacheva::PhoneBook::size() const
{
  return contents_.size();
}
