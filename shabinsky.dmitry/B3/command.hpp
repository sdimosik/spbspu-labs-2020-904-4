//
// Created by sdimosik on 29.10.2020.
//

#ifndef B3_COMMAND_HPP
#define B3_COMMAND_HPP

#include <istream>
#include <iostream>
#include "phoneBookContainer.hpp"

const std::string INVALID_COMMAND = "<INVALID COMMAND>\n";
const std::string INVALID_STEP = "<INVALID STEP>\n";

bool isNameValid(std::string &name);

bool isNumberValid(std::string &number);

bool isBookmarkValid(std::string &bookmark);

void addCommand(phoneBookContainer &phoneBook, std::istream &sin);

void storeCommand(phoneBookContainer &phoneBook, std::istream &sin);

void insertCommand(phoneBookContainer &phoneBook, std::istream &sin);

void eraseCommand(phoneBookContainer &phoneBook, std::istream &sin);

void showCommand(phoneBookContainer &phoneBook, std::istream &sin);

void moveCommand(phoneBookContainer &phoneBook, std::istream &sin);

void parseCommand(phoneBookContainer &phoneBook, const std::string &command, std::istream &sin);

bool isNameValid(std::string &name)
{
  if (name.empty() || name.front() != '\"' || name.back() != '\"')
  {
    return false;
  }
  name.erase(name.begin());
  name.erase(--name.end());
  
  size_t digitIndex = 0;
  while (digitIndex < name.size())
  {
    if (name[digitIndex] == '\\')
    {
      name.erase(digitIndex, 1);
    }
    digitIndex++;
  }
  
  return !name.empty();
}

bool isNumberValid(std::string &number)
{
  for (auto &digit: number)
  {
    if (!std::isdigit(digit))
    {
      return false;
    }
  }
  return !number.empty();
}

bool isBookmarkValid(std::string &bookmark)
{
  for (auto &symbol: bookmark)
  {
    if (!isalnum(symbol) && (symbol != '-'))
    {
      return false;
    }
  }
  return !bookmark.empty();
}

void addCommand(phoneBookContainer &phoneBook, std::istream &sin)
{
  std::string number;
  sin >> std::ws >> number;
  
  std::string name;
  std::getline(sin >> std::ws, name);
  
  if (!isNumberValid(number) || !isNameValid(name))
  {
    std::cout << INVALID_COMMAND;
    return;
  }
  
  phoneBook.add(PhoneBook::Note{number, name});
}

void storeCommand(phoneBookContainer &phoneBook, std::istream &sin)
{
  std::string bookmark;
  sin >> std::ws >> bookmark;
  
  std::string newBookmark;
  sin >> std::ws >> newBookmark;
  
  if (!sin.eof() || !isBookmarkValid(bookmark) || !isBookmarkValid(newBookmark))
  {
    std::cout << INVALID_COMMAND;
  }
  else
  {
    phoneBook.storeBookmark(bookmark, newBookmark);
  }
}

void insertCommand(phoneBookContainer &phoneBook, std::istream &sin)
{
  std::string direction;
  sin >> std::ws >> direction;
  
  std::string bookmark;
  sin >> std::ws >> bookmark;
  
  std::string number;
  sin >> std::ws >> number;
  
  std::string name;
  
  std::getline(sin >> std::ws, name);
  
  if (!isBookmarkValid(bookmark) || !isNumberValid(number) || !isNameValid(name))
  {
    std::cout << INVALID_COMMAND;
    return;
  }
  
  PhoneBook::Note newNote{number, name};
  if (direction == "before")
  {
    phoneBook.insert(bookmark, phoneBookContainer::InsertType::BEFORE, newNote);
  }
  else if (direction == "after")
  {
    phoneBook.insert(bookmark, phoneBookContainer::InsertType::AFTER, newNote);
  }
  else
  {
    std::cout << INVALID_COMMAND;
  }
}

void eraseCommand(phoneBookContainer &phoneBook, std::istream &sin)
{
  std::string bookmark;
  sin >> std::ws >> bookmark;
  
  if (!sin.eof() || !isBookmarkValid(bookmark))
  {
    std::cout << INVALID_COMMAND;
  }
  else
  {
    phoneBook.removeNote(bookmark);
  }
}

void showCommand(phoneBookContainer &phoneBook, std::istream &sin)
{
  std::string bookmark;
  sin >> std::ws >> bookmark;
  
  if (!sin.eof() || !isBookmarkValid(bookmark))
  {
    std::cout << INVALID_COMMAND;
  }
  else
  {
    phoneBook.showNote(bookmark);
  }
}

void moveCommand(phoneBookContainer &phoneBook, std::istream &sin)
{
  std::string bookmark;
  sin >> std::ws >> bookmark;
  
  if (!isBookmarkValid(bookmark))
  {
    std::cout << INVALID_COMMAND;
    return;
  }
  
  std::string steps;
  sin >> std::ws >> steps;
  
  if (!sin.eof())
  {
    std::cout << INVALID_COMMAND;
  }
  else if (steps == "first")
  {
    phoneBook.moveBookmark(bookmark, phoneBookContainer::MoveType::FIRST);
  }
  else if (steps == "last")
  {
    phoneBook.moveBookmark(bookmark, phoneBookContainer::MoveType::FIRST);
  }
  else
  {
    if (steps.empty())
    {
      std::cout << INVALID_STEP << "dwa";
      return;
    }
    int sign = 1;
    if (steps[0] == '-')
    {
      sign = -1;
      steps.erase(steps.begin());
    }
    else if (steps[0] == '+')
    {
      steps.erase(steps.begin());
    }
    
    if (!isNumberValid(steps))
    {
      std::cout << INVALID_STEP;
    }
    else
    {
      phoneBook.moveBookmark(bookmark, stoi(steps) * sign);
    }
  }
}

void parseCommand(phoneBookContainer &phoneBook, const std::string &command, std::istream &sin)
{
  if (command == "add")
  {
    addCommand(phoneBook, sin);
  }
  else if (command == "store")
  {
    storeCommand(phoneBook, sin);
  }
  else if (command == "insert")
  {
    insertCommand(phoneBook, sin);
  }
  else if (command == "delete")
  {
    eraseCommand(phoneBook, sin);
  }
  else if (command == "show")
  {
    showCommand(phoneBook, sin);
  }
  else if (command == "move")
  {
    moveCommand(phoneBook, sin);
  }
  else
  {
    std::cout << INVALID_COMMAND;
  }
}

#endif //B3_COMMAND_HPP
