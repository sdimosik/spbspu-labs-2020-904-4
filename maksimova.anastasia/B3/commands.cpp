#include <limits>
#include <string>
#include <stdexcept>
#include <iostream>

#include "phoneBookInterface.hpp"
#include "commands.hpp"
#include "parse.hpp"

function printError()
{
  return [](phoneBookInterface &, std::ostream &out)
  {
    out << "<INVALID COMMAND>" << '\n';
  };
}

function add(std::istream &sin)
{
  std::string number = parseNumber(sin);
  std::string name = parseName(sin);
  return [number, name](phoneBookInterface &phoneBook, std::ostream&)
  {
    phoneBook.addNote({number, name});
  };
}

function store(std::istream &sin)
{
  std::string bookmark = getCheckedBookmark(sin);
  std::string newBookmark = getCheckedBookmark(sin);
  return [bookmark, newBookmark](phoneBookInterface &phoneBook, std::ostream &)
  {
    phoneBook.storeBookmark(bookmark, newBookmark);
  };
}

function insert(std::istream &sin)
{
  std::string position;
  sin >> position;
  std::string bookmark = getCheckedBookmark(sin);
  std::string  number = parseNumber(sin);
  std::string name = parseName(sin);
  phoneBook::phoneNote note{number, name};
  if(position == "before")
  {
    return [bookmark, note](phoneBookInterface &phoneBook, std::ostream &)
    {
      phoneBook.insertBefore(bookmark, note);
    };
  }
  else if (position == "after")
  {
    return [bookmark, note](phoneBookInterface &phoneBook, std::ostream &)
    {
      phoneBook.insertAfter(bookmark, note);
    };
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }
}

function erase(std::istream &sin)
{
  std::string bookmark = getCheckedBookmark(sin);
  return [bookmark](phoneBookInterface &phoneBook, std::ostream &)
  {
    phoneBook.eraseNote(bookmark);
  };
}

function show(std::istream &sin)
{
  std::string bookmark = getCheckedBookmark(sin);
  return [bookmark](phoneBookInterface &phoneBook, std::ostream &)
  {
    phoneBook.showNote(std::cout, bookmark);
  };
}

function move(std::istream &sin)
{
  std::string bookmark = getCheckedBookmark(sin);
  std::string steps;
  sin >> steps;
  return [bookmark, steps](phoneBookInterface &phoneBook, std::ostream &out)
  {
    if (steps == "first")
    {
      phoneBookInterface::position pos = phoneBookInterface::position::FIRST;
      phoneBook.moveBookmark(bookmark, pos);
      return;
    }
    if (steps == "last")
    {
      phoneBookInterface::position pos = phoneBookInterface::position::LAST;
      phoneBook.moveBookmark(bookmark, pos);
      return;
    }
    int intSteps;
    if(!isValidSteps(steps))
    {
      out << "<INVALID STEP>" << '\n';
      return;
    }
    intSteps = stepsToInt(steps);
    phoneBook.moveBookmark(bookmark, intSteps);
  };
}

std::istream &operator>>(std::istream &input, function &function)
{
  try
  {
    std::string command;
    input >> command;
    auto it =  TABLE.find(command);
    if(it == TABLE.end())
    {
      function = printError();
      return input;
    }
    function = (*it).second(input);
  }
  catch (std::invalid_argument &error)
  {
    if(char(input.unget().peek()) != '\n')
    {
      input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    function = printError();
  }
  return input;
}
