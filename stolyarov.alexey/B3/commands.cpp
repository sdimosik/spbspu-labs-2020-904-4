#include "commands.hpp"
#include <cctype>
#include <limits>
#include <stdexcept>
#include <iostream>
#include <algorithm>

std::string checkNumber(std::istream& sin)
{
  std::string number;
  sin >> number;

  if (number.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  for (auto& digit : number)
  {
    if (!std::isdigit(digit))
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
  return number;
}

std::string checkBookmarkName(std::istream& sin)
{
  std::string bookmark;
  sin >> bookmark;

  if (bookmark.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  for (auto& symbol : bookmark)
  {
    if (!isalnum(symbol) && (symbol != '-'))
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
  return bookmark;
}

std::string checkName(std::istream& sin)
{
  std::string name;
  sin >> name;
  if (!sin.eof())
  {
    std::string temp;
    std::getline(sin, temp);
    name += temp;
  }

  if (name.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  if ((name.front() != '\"') || (name.back() != '\"'))
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::string::iterator iter = std::remove(name.begin(), name.end(), '\\');
  name.erase(iter, name.end());
  name.erase(0, 1);
  name.pop_back();
  return name;
}

int getSteps(const std::string& step)
{
  auto it = step.begin();
  if (step[0] == '+' || step[0] == '-')
  {
    it++;
  }
  for (; it < step.end(); it++)
  {
    if (!isdigit(*it))
    {
      throw std::invalid_argument("");
    }
  }
  return std::stoi(step);
}

function add(std::istream& sin)
{
  std::string number = checkNumber(sin);
  std::string name = checkName(sin);
  return [number, name](PhoneBookInterface& phoneBook, std::ostream&)
  {
    PhoneBook::PhoneBookNote newNote{ number, name };
    phoneBook.add(newNote);
  };
}

function store(std::istream& sin)
{
  std::string bookmark = checkBookmarkName(sin);
  std::string newBookmark = checkBookmarkName(sin);
  return [bookmark, newBookmark](PhoneBookInterface& phoneBook, std::ostream&)
  {
    phoneBook.store(bookmark, newBookmark);
  };
}

function insert(std::istream& sin)
{
  std::string direction;
  sin >> direction;
  std::string bookmark = checkBookmarkName(sin);
  std::string number = checkNumber(sin);
  std::string name = checkName(sin);
  PhoneBook::PhoneBookNote newNote{ number, name };
  if (direction == "before")
  {
    return [bookmark, newNote](PhoneBookInterface& phoneBook, std::ostream&)
    {
      phoneBook.insertBefore(bookmark, newNote);
    };
  }
  else if (direction == "after")
  {
    return [bookmark, newNote](PhoneBookInterface& phoneBook, std::ostream&)
    {
      phoneBook.insertAfter(bookmark, newNote);
    };
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }
}

function deleteBookmark(std::istream& sin)
{
  std::string bookmark = checkBookmarkName(sin);
  return [bookmark](PhoneBookInterface& phoneBook, std::ostream&)
  {
    phoneBook.deleteBookmarkNote(bookmark);
  };
}

function show(std::istream& sin)
{
  std::string bookmark = checkBookmarkName(sin);
  return [bookmark](PhoneBookInterface& phoneBook, std::ostream&)
  {
    phoneBook.showBookmark(bookmark);
  };
}

function move(std::istream& sin)
{
  std::string bookmark = checkBookmarkName(sin);
  std::string step;
  sin >> step;
  return [bookmark, step](PhoneBookInterface& phoneBook, std::ostream& out)
  {
    if (step == "first")
    {
      PhoneBookInterface::MovePosition position = PhoneBookInterface::MovePosition::FIRST;
      phoneBook.moveBookmark(bookmark, position);
      return;
    }

    if (step == "last")
    {
      PhoneBookInterface::MovePosition position = PhoneBookInterface::MovePosition::LAST;
      phoneBook.moveBookmark(bookmark, position);
      return;
    }

    int offset;
    try
    {
      offset = getSteps(const_cast<std::string&>(step));
    }
    catch (std::invalid_argument& e)
    {
      out << "<INVALID STEP>" << '\n';
      return;
    }
    phoneBook.moveBookmark(bookmark, offset);
  };
}

std::istream& operator>>(std::istream& sin, function& function)
{
  try
  {
    std::string command;
    sin >> command;

    auto it = TABLE.find(command);

    if (it == TABLE.end())
    {
      function = printException();
      return sin;
    }
    function = (*it).second(sin);
  }
  catch (std::invalid_argument& e)
  {
    if (char(sin.unget().peek()) != '\n')
    {
      sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    function = printException();
  }
  return sin;
}

function printException()
{
  return [](PhoneBookInterface&, std::ostream& out)
  {
    out << "<INVALID COMMAND>" << '\n';
  };
}
