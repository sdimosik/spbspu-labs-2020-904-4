#include "commands.hpp"
#include <limits>
#include "dataValidation.hpp"
#include "phoneBookInterface.hpp"

function add(std::istream &sin)
{
  std::string number = getCheckedNumber(sin);
  std::string name = getCheckedName(sin);
  return [number, name](PhoneBookInterface &phoneBook, std::ostream &)
  {
    PhoneBook::Note newNote{number, name};
    phoneBook.addNote(newNote);
  };
}

function store(std::istream &sin)
{
  std::string bookmark = getCheckedBookmark(sin);
  std::string newBookmark = getCheckedBookmark(sin);
  return [bookmark, newBookmark](PhoneBookInterface &phoneBook, std::ostream &)
  {
    phoneBook.storeBookmark(bookmark, newBookmark);
  };
}

function insert(std::istream &sin)
{
  std::string direction;
  sin >> direction;
  std::string bookmark = getCheckedBookmark(sin);
  std::string number = getCheckedNumber(sin);
  std::string name = getCheckedName(sin);

  PhoneBook::Note newNote{number, name};

  if (direction == "before")
  {
    return [bookmark, newNote](PhoneBookInterface &phoneBook, std::ostream &)
    {
      phoneBook.insertNoteBefore(bookmark, newNote);
    };
  }
  else if (direction == "after")
  {
    return [bookmark, newNote](PhoneBookInterface &phoneBook, std::ostream &)
    {
      phoneBook.insertNoteAfter(bookmark, newNote);
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

  return [bookmark](PhoneBookInterface &phoneBook, std::ostream &)
  {
    phoneBook.eraseNote(bookmark);
  };
}

function show(std::istream &sin)
{
  std::string bookmark = getCheckedBookmark(sin);
  return [bookmark](PhoneBookInterface &phoneBook, std::ostream &)
  {
    phoneBook.showNote(bookmark);
  };
}

function move(std::istream &sin)
{
  std::string bookmark = getCheckedBookmark(sin);
  std::string steps;
  sin >> steps;

  return [bookmark, steps](PhoneBookInterface &phoneBook, std::ostream &out)
  {
    if (steps == "first")
    {
      PhoneBookInterface::MovePosition position = PhoneBookInterface::MovePosition::FIRST;
      phoneBook.moveBookmark(bookmark, position);
      return;
    }

    if (steps == "last")
    {
      PhoneBookInterface::MovePosition position = PhoneBookInterface::MovePosition::LAST;
      phoneBook.moveBookmark(bookmark, position);
      return;
    }
    int intSteps;
    try
    {
      intSteps = getSteps(steps);
    }
    catch(const std::logic_error&)
    {
      out << "<INVALID STEP>" << '\n';
      return;
    }
    phoneBook.moveBookmark(bookmark, intSteps);
  };
}

function printException()
{
  return [](PhoneBookInterface &, std::ostream &out)
  {
    out << "<INVALID COMMAND>" << '\n';
  };
}

std::istream &operator>>(std::istream &input, function &function)
{
  try
  {
    std::string command;
    input >> command;

    auto it = CALL_TABLE.find(command);

    if (it == CALL_TABLE.end())
    {
      function = printException();
      return input;
    }

    function = (*it).second(input);
  }
  catch (std::invalid_argument &error)
  {
    if (char(input.unget().peek()) != '\n')
    {
      input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    function = printException();
  }

  return input;
}
