#include <limits>
#include "commands.hpp"
#include "isValidDate.hpp"

function add(std::istream &in)
{
  std::string number = checkNumber(in);
  std::string name = checkName(in);

  return [number, name](PhoneBookInterface &phoneBookInterface, std::ostream &)
  {
    PhoneBook::Records newRecord{number, name};
    phoneBookInterface.executeAdd(newRecord);
  };
}

function store(std::istream &in)
{
  std::string bookmark = checkBookmark(in);
  std::string newBookmark = checkBookmark(in);

  return [bookmark, newBookmark](PhoneBookInterface &phoneBookInterface, std::ostream &)
  {
    phoneBookInterface.executeStore(bookmark, newBookmark);
  };

}

function insert(std::istream &in)
{
  std::string position;
  in >> position;

  std::string bookmark = checkBookmark(in);
  std::string number = checkNumber(in);
  std::string name = checkName(in);

  PhoneBook::Records newRecord{number, name};
  if (position == "before")
  {
    return [bookmark, newRecord](PhoneBookInterface &phoneBookInterface, std::ostream &)
    {
      phoneBookInterface.executeInsertBefore(bookmark, newRecord);
    };

  }else if (position == "after")
  {
    return [bookmark, newRecord](PhoneBookInterface &phoneBookInterface, std::ostream &)
    {
      phoneBookInterface.executeInsertAfter(bookmark, newRecord);
    };
  } else {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }
}

function erase(std::istream &in)
{
  std::string bookmark = checkBookmark(in);

  return [bookmark](PhoneBookInterface &phoneBookInterface, std::ostream &)
  {
    phoneBookInterface.executeRemove(bookmark);
  };
}

function show(std::istream &in)
{
  std::string bookmark = checkBookmark(in);
  return [bookmark](PhoneBookInterface &phoneBookInterface, std::ostream &)
  {
    phoneBookInterface.executeShow(bookmark);
  };
}

function move(std::istream &in)
{
  std::string bookmark = checkBookmark(in);
  std::string step;
  in >> step;

  return [bookmark, step](PhoneBookInterface &phoneBookInterface, std::ostream &out)
  {
    if (step == "first")
    {
      phoneBookInterface.executeMove(bookmark, PhoneBookInterface::MovePosition::FIRST);
      return;
    }

    if (step == "last")
    {
      phoneBookInterface.executeMove(bookmark, PhoneBookInterface::MovePosition::LAST);
      return;
    }

    int finalStep;
    try
    {
      finalStep = getStep(step);
    }
    catch(const std::logic_error&)
    {
      out << "<INVALID STEP>" << '\n';
      return;
    }

    phoneBookInterface.executeMove(bookmark, finalStep);
  };
}

function printOutErrors()
{
  return [](PhoneBookInterface &, std::ostream &out)
  {
    out << "<INVALID COMMAND>" << '\n';
  };
}

std::istream &operator>>(std::istream &in, function &function)
{
  try
  {
    std::string command;
    in >> command;

    auto iter = COMMAND_MEANS.find(command);

    if (iter == COMMAND_MEANS.end())
    {
      function = printOutErrors();
      return in;
    }

    function = (*iter).second(in);
  }
  catch (std::invalid_argument &error)
  {
    if (char(in.unget().peek()) != '\n')
    {
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    function = printOutErrors();
  }

  return in;
}

