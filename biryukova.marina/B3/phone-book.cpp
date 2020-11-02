#include "phone-book.hpp"
#include <stdexcept>
#include <iterator>
#include <cstdlib>

void PhoneBook::insertAfter(const std::string& number, const std::string& name, IteratorType iter)
{
  PhoneBookNote temp{number, name};
  phonebook_.insert(std::next(iter), temp);
}

void PhoneBook::insertBefore(const std::string& number, const std::string& name, IteratorType iter)
{
  PhoneBookNote temp{number, name};
  phonebook_.insert(iter, temp);
}

void PhoneBook::replaceCurrent(const std::string& number, const std::string& name, IteratorType iter)
{
  iter->number = number;
  iter->name = name;
}

void PhoneBook::insertToEnd(const std::string& number, const std::string& name)
{
  PhoneBookNote temp{number, name};
  phonebook_.push_back(temp);
}

void PhoneBook::deleteNote(IteratorType iter)
{
  phonebook_.erase(iter);
}

void PhoneBook::showCurrent(std::ostream& out, IteratorType iter) const
{
  out << iter->number << " " << iter->name << '\n';
}

PhoneBook::IteratorType PhoneBook::begin() noexcept
{
  return phonebook_.begin();
}

PhoneBook::IteratorType PhoneBook::end() noexcept
{
  return phonebook_.end();
}

bool PhoneBook::isEmpty() const noexcept
{
  return phonebook_.empty();
}

size_t PhoneBook::size() const noexcept
{
  return phonebook_.size();
}
