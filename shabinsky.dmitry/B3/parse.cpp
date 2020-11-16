#include <istream>
#include <iostream>
#include "parse.hpp"

namespace parse
{
  bool isNameValidPlusCorrect(std::string &name)
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
  
  void addCommand(bool &execCommand, std::string &number, std::string &name, std::istream &sin)
  {
    sin >> std::ws >> number;
    std::getline(sin >> std::ws, name);
    
    if (!isNumberValid(number) || !isNameValidPlusCorrect(name))
    {
      std::cout << INVALID_COMMAND;
      execCommand = false;
    }
  }
  
  void storeCommand(bool &execCommand, std::string &bookmark, std::string &newBookmark, std::istream &sin)
  {
    sin >> std::ws >> bookmark;
    sin >> std::ws >> newBookmark;
    
    if (!sin.eof() || !isBookmarkValid(bookmark) || !isBookmarkValid(newBookmark))
    {
      std::cout << INVALID_COMMAND;
      execCommand = false;
    }
  }
  
  void
  insertCommand(bool &execCommand, std::string &direction, std::string &bookmark, std::string &number,
                std::string &name,
                std::istream &sin)
  {
    sin >> std::ws >> direction;
    sin >> std::ws >> bookmark;
    sin >> std::ws >> number;
    std::getline(sin >> std::ws, name);
    
    if (!isBookmarkValid(bookmark) || !isNumberValid(number) || !isNameValidPlusCorrect(name))
    {
      std::cout << INVALID_COMMAND;
      execCommand = false;
      return;
    }
    if (direction != "before" && direction != "after")
    {
      std::cout << INVALID_COMMAND;
      execCommand = false;
    }
  }
  
  void eraseCommand(bool &execCommand, std::string &bookmark, std::istream &sin)
  {
    sin >> std::ws >> bookmark;
    
    if (!sin.eof() || !isBookmarkValid(bookmark))
    {
      std::cout << INVALID_COMMAND;
      execCommand = false;
    }
  }
  
  void showCommand(bool &execCommand, std::string &bookmark, std::istream &sin)
  {
    sin >> std::ws >> bookmark;
    
    if (!sin.eof() || !isBookmarkValid(bookmark))
    {
      std::cout << INVALID_COMMAND;
      execCommand = false;
    }
  }
  
  void moveCommand(bool &execCommand, std::string &bookmark, std::string &steps, std::istream &sin)
  {
    sin >> std::ws >> bookmark;
    if (!isBookmarkValid(bookmark))
    {
      std::cout << INVALID_COMMAND;
      execCommand = false;
      return;
    }
    sin >> std::ws >> steps;
    if (!sin.eof())
    {
      std::cout << INVALID_COMMAND;
      execCommand = false;
      return;
    }
    if (steps.empty())
    {
      std::cout << INVALID_STEP << "dwa";
      execCommand = false;
      return;
    }
  }
  
  void
  exec(bool &execCommand, const std::string &command, std::istream &sin, std::string &direction, std::string &bookmark,
       std::string &newBookmark,
       std::string &number, std::string &name, std::string &steps)
  {
    if (command == "add")
    {
      addCommand(execCommand, number, name, sin);
    }
    else if (command == "store")
    {
      storeCommand(execCommand, bookmark, newBookmark, sin);
    }
    else if (command == "insert")
    {
      insertCommand(execCommand, direction, bookmark, number, name, sin);
    }
    else if (command == "delete")
    {
      eraseCommand(execCommand, bookmark, sin);
    }
    else if (command == "show")
    {
      showCommand(execCommand, bookmark, sin);
    }
    else if (command == "move")
    {
      moveCommand(execCommand, bookmark, steps, sin);
    }
    else
    {
      std::cout << INVALID_COMMAND;
      execCommand = false;
    }
  }
}
