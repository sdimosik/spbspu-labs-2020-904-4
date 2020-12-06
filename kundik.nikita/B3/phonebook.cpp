#include "phonebook.hpp"

#include <iostream>

void PhoneBook::showNote(Iterator it)
{
  std::cout << it->number << ' ' << it->name << '\n';
}

PhoneBook::Iterator PhoneBook::insertBefore(PhoneBook::Record& newRecord, Iterator it)
{
  return listOfRecords_.insert(it, newRecord);
}

PhoneBook::Iterator PhoneBook::insertAfter(PhoneBook::Record& newRecord, Iterator it)
{
  return listOfRecords_.insert(++it, newRecord);
}

void PhoneBook::insertInTheEnd(PhoneBook::Record& newRecord)
{
  listOfRecords_.push_back(newRecord);
}

PhoneBook::Iterator PhoneBook::deleteRecord(Iterator it)
{
  if (listOfRecords_.empty())
  {
    return listOfRecords_.end();
  }
  return listOfRecords_.erase(it);
}

PhoneBook::Iterator PhoneBook::getBegin()
{
  return listOfRecords_.begin();
}

PhoneBook::Iterator PhoneBook::getEnd()
{
  return listOfRecords_.end();
}
