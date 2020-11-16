#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "phone-book.hpp"

void phoneBook::showCurrentRecord(std::ostream& out, Iterator iter) const
{
  out << iter->name << " " << iter->number << "\n";
}

void phoneBook::insertBefore(const std::string& number, const std::string& name, Iterator iter)
{
  record_t temp{number, name};
  list.insert(iter, temp);

}
void phoneBook::insertAfter(const std::string& number, const std::string& name, Iterator iter)
{
  record_t temp{number, name};
  list.insert(std::next(iter), temp);

}
void phoneBook::insertAtEnd(const std::string& number, const std::string& name)
{
  record_t temp{number, name};
  list.push_back(temp);

}

void phoneBook::replaceCurrentRecord(const std::string& number, const std::string& name, Iterator iter)
{
  iter->number = number;
  iter->name = name;

}

void phoneBook::remove(Iterator iter)
{
  list.erase(iter);
}

phoneBook::Iterator phoneBook::begin() noexcept
{
  return list.begin();
}

phoneBook::Iterator phoneBook::end() noexcept
{
  return list.end();
}

bool phoneBook::isEmpty() const noexcept
{
  return list.empty();
}

size_t phoneBook::getSize() const noexcept
{
  return list.size();
}
