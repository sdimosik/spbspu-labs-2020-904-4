#include <stdexcept>
#include <iostream>
#include <functional>
#include <sstream>

#include "phoneBookInterface.hpp"

bool isNumberCorrect(const std::string& number)
{
  if(number.empty())
  {
    return false;
  }
  auto it = number.begin();
  while(it != number.end())
  {
    if(!isdigit(*it))
    {
      return false;
    }
    it++;
  }
  return true;
}

bool isBookMarkNameCorrect(const std::string& bookMark)
{
  if(bookMark.empty())
  {
    return false;
  }
  auto it = bookMark.begin();
  while(it != bookMark.end())
  {
    if((isalnum(*it) == 0) && (*it != '-'))
    {
      return false;
    }
    it++;
  }
  return true;
}

bool isNameCorrect(const std::string& name)
{
  if(name.front() != '\"' || name.back() != '\"' || name.empty())
  {
    return false;
  }
  return true;
}

void formatName(std::string& name)
{
  name.erase(name.begin());
  name.erase(--name.end());
  auto it = name.begin();
  while(it != name.end())
  {
    if(*it == '\\')
    {
      it = name.erase(it);
    }
    else
    {
      it++;
    }
  }
}

std::function<void(PhoneBookInterface&)> addRecord(std::istream& istream)
{
  std::string number, name, restPartOfName;
  istream >> std::ws >> number;
  std::getline(istream >> std::ws, name);
  if(!isNameCorrect(name) || !isNumberCorrect(number))
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }
  formatName(name);
  if(name.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }
  return [name, number](PhoneBookInterface& phoneBook)
  {
    PhoneBook::Record newRecord{number, name};
    phoneBook.addRecord(newRecord);
  };
}

std::function<void(PhoneBookInterface&)> storeMark(std::istream& istream)
{
  std::string markName, newMarkName;
  istream >> std::ws >> markName;
  istream >> std::ws >> newMarkName;
  if(!istream.eof() || !isBookMarkNameCorrect(markName) || !isBookMarkNameCorrect(newMarkName))
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }
  return [markName, newMarkName](PhoneBookInterface& phoneBook)
  {
    phoneBook.storeMark(markName, newMarkName);
  };
}

std::function<void(PhoneBookInterface&)> insertRecord(std::istream& istream)
{
  std::string position, markName, number, name;
  istream >> std::ws >> position;
  istream >> std::ws >> markName;
  istream >> std::ws >> number;
  std::getline(istream >> std::ws, name);
  if((position != "before" && position != "after") || !isNameCorrect(name)
      || !isBookMarkNameCorrect(markName) || !isNumberCorrect(number))
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }
  formatName(name);
  if(name.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }
  return [name, number, markName, position](PhoneBookInterface& phoneBook)
  {
    PhoneBook::Record newRecord{number, name};
    if(position == "before")
    {
      phoneBook.insertBefore(newRecord, markName);
    }
    else
    {
      phoneBook.insertAfter(newRecord, markName);
    }
  };
}

std::function<void(PhoneBookInterface&)> deleteMark(std::istream& istream)
{
  std::string markName;
  istream >> std::ws >> markName;
  if(!isBookMarkNameCorrect(markName))
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }
  return [markName](PhoneBookInterface& phoneBook)
  {
    phoneBook.deleteRecordOnMark(markName);
  };
}

std::function<void(PhoneBookInterface&)> showMark(std::istream& istream)
{
  std::string markName;
  istream >> std::ws >> markName;
  if(!isBookMarkNameCorrect(markName))
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }
  return [markName](PhoneBookInterface& phoneBook)
  {
    phoneBook.showMark(markName);
  };
}

std::function<void(PhoneBookInterface&)> moveMark(std::istream& istream)
{
  std::string markName, steps;
  istream >> std::ws >> markName;
  if(!isBookMarkNameCorrect(markName))
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }
  istream >> std::ws >> steps;
  int sign = 1;
  if(steps != "first" && steps != "last")
  {
    if(steps[0] == '-')
    {
      sign = -1;
      steps.erase(steps.begin());
    }
    else if(steps[0] == '+')
    {
      steps.erase(steps.begin());
    }
    if(!isNumberCorrect(steps))
    {
      throw std::invalid_argument("<INVALID STEP>\n");
    }
  }
  return [markName, steps, sign](PhoneBookInterface& phoneBook)
  {
    if(steps == "first")
    {
      PhoneBookInterface::MovePositionKeyWords pos;
      pos = PhoneBookInterface::MovePositionKeyWords::FIRST;
      phoneBook.moveMark(markName, pos);
    }
    else if(steps == "last")
    {
      PhoneBookInterface::MovePositionKeyWords pos;
      pos = PhoneBookInterface::MovePositionKeyWords::LAST;
      phoneBook.moveMark(markName, pos);
    }
    else
    {
      phoneBook.moveMark(markName, (std::stoi(steps) * sign));
    }
  };
}
