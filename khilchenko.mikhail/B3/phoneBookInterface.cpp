#include "phoneBookInterface.hpp"

#include <iostream>

PhoneBookInterface::PhoneBookInterface(std::unique_ptr<PhoneBook>&& other)
{
  phoneBook_ = std::move(other);
  bookMarks_.insert(std::make_pair("current", phoneBook_->getBegin()));
}

void PhoneBookInterface::addRecord(PhoneBook::Record& newRecord)
{
  phoneBook_->insertInTheEnd(newRecord);
  if(phoneBook_->getBegin() == --phoneBook_->getEnd())
  {
    bookMarks_["current"] = phoneBook_->getBegin();
  }
}

void PhoneBookInterface::storeMark(const std::string& markName, const std::string& newMarkName)
{
  auto it = bookMarks_.find(markName);
  if(it != bookMarks_.end())
  {
    auto recordIt = it->second;
    bookMarks_.insert(std::make_pair(newMarkName, recordIt));
  }
  else
  {
    std::cout << "<INVALID BOOKMARK>\n";
  }
}

void PhoneBookInterface::insertBefore(PhoneBook::Record& newRecord, const std::string& markName)
{
  if(markName == "current" && (phoneBook_->getBegin() == phoneBook_->getEnd()))
  {
    addRecord(newRecord);
  }
  else
  {
    auto it = bookMarks_.find(markName);
    if(it != bookMarks_.end())
    {
      phoneBook_->insertBefore(newRecord, it->second);
      if(bookMarks_.size() == 1)
      {
        bookMarks_["current"] = phoneBook_->getBegin();
      }
    }
    else
    {
      std::cout << "<INVALID BOOKMARK>\n";
    }
  }
}

void PhoneBookInterface::insertAfter(PhoneBook::Record& newRecord, const std::string& markName)
{
  if(markName == "current" && (phoneBook_->getBegin() == phoneBook_->getEnd()))
  {
    addRecord(newRecord);
  }
  else
  {
    auto it = bookMarks_.find(markName);
    if(it != bookMarks_.end())
    {
      phoneBook_->insertAfter(newRecord, it->second);
      if(bookMarks_.size() == 1)
      {
        bookMarks_["current"] = phoneBook_->getBegin();
      }
    }
    else
    {
      std::cout << "<INVALID BOOKMARK>\n";
    }
  }
}

void PhoneBookInterface::deleteRecordOnMark(const std::string& markName)
{
  auto it = bookMarks_.find(markName);
  if(it == bookMarks_.end())
  {
    std::cout << "<INVALID BOOKMARK>\n";
    return;
  }
  auto deleteIt = it->second;
  for(auto i = bookMarks_.begin(); i != bookMarks_.end(); i++)
  {
    if(i->second == deleteIt)
    {
      if(std::next(i->second) == phoneBook_->getEnd())
      {
        i->second = phoneBook_->getBegin();
      }
      else
      {
        i->second = std::next(deleteIt);
      }
    }
  }
  phoneBook_->deleteRecord(deleteIt);
}

void PhoneBookInterface::showMark(const std::string& markName)
{
  auto it = bookMarks_.find(markName);
  if(it == bookMarks_.end())
  {
    std::cout << "<INVALID BOOKMARK>\n";
  }
  else if(phoneBook_->getBegin() == phoneBook_->getEnd())
  {
    std::cout << "<EMPTY>\n";
  }
  else
  {
    phoneBook_->showNote(it->second);
  }
}

void PhoneBookInterface::moveMark(const std::string& markName, int step)
{
  auto it = bookMarks_.find(markName);
  if(it != bookMarks_.end())
  {
    bool isStepPositive = true;
    if(step < 0)
    {
      step *= -1;
      isStepPositive = false;
    }
    for(int i = 0; i < step; i++)
    {
      if(isStepPositive)
      {
        if(it->second == --phoneBook_->getEnd())
        {
          break;
        }
        it->second++;
      }
      else
      {
        if(it->second == phoneBook_->getBegin())
        {
          break;
        }
        it->second--;
      }
    }
  }
  else
  {
    std::cout << "<INVALID BOOKMARK>\n";
  }
}

void PhoneBookInterface::moveMark(const std::string& markName, const MovePositionKeyWords& pos)
{
  auto it = bookMarks_.find(markName);
  if(it != bookMarks_.end())
  {
    if(pos == MovePositionKeyWords::FIRST)
    {
      it->second = phoneBook_->getBegin();
    }
    else
    {
      it->second = --phoneBook_->getEnd();
    }
  }
  else
  {
    std::cout << "<INVALID BOOKMARK>\n";
  }
}
