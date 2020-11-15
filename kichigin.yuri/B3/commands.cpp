#include "commands.hpp"
#include <iostream>

using namespace std::placeholders;

std::map<std::string, std::function<void(std::istream& istream, BookInterface& telephoneBookInterface)>> commandList
    = { {"add", add},
        {"store", store},
        {"insert", insert},
        {"delete", deleteNote},
        {"show", show},
        {"move", move} };

AddCommand parseAdd(std::istream& istream)
{
  std::string number, name;

  istream >> std::ws >> number;
  number = checkNumber(number);

  istream >> std::ws;
  std::getline(istream, name);
  name = checkName(name);

  if (number.empty() || name.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
  }

  return {std::make_pair(name, number)};
}

StoreCommand parseStore(std::istream& istream)
{
  std::string bookmark, newBookmark;

  istream >> std::ws >> bookmark;
  bookmark = checkBookmark(bookmark);

  istream >> std::ws >> newBookmark;
  newBookmark = checkBookmark(newBookmark);

  if (!istream.eof() || bookmark.empty() || newBookmark.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
  }
  return { bookmark, newBookmark };
}

InsertCommand parseInsert(std::istream& istream)
{
  std::string position, bookmark, number, name;

  istream >> std::ws >> position;

  istream >> std::ws >> bookmark;
  bookmark = checkBookmark(bookmark);

  istream >> std::ws >> number;
  number = checkNumber(number);

  istream >> std::ws;
  std::getline(istream, name);
  name = checkName(name);

  if (bookmark.empty() || number.empty() || name.empty() || (position == "before" && position == "after"))
  {
    std::cout << "<INVALID COMMAND>\n";
  }

  TelephoneBook::Note note = std::make_pair(name, number);
  if (position == "before" || position == "after")
  {
    return { bookmark, position, note };
  }
  else
  {
    return { bookmark, "", note };
  }
}

DeleteCommand parseDelete(std::istream& istream)
{
  std::string bookmark;
  istream >> std::ws >> bookmark;
  bookmark = checkBookmark(bookmark);

  if (!istream.eof() || bookmark.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
  }
  return { bookmark };
}

ShowCommand parseShow(std::istream& istream)
{
  std::string bookmark;
  istream >> std::ws >> bookmark;
  bookmark = checkBookmark(bookmark);

  if (!istream.eof() || bookmark.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
  }
  return { bookmark };
}

MoveCommand parseMove(std::istream& istream)
{
  std::string bookmark, steps;
  istream >> std::ws >> bookmark;
  bookmark = checkBookmark(bookmark);

  if (bookmark.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return { "", std::make_pair(details::UnionParameter::INVALID, details::MoveParameter(0)) };
  }

  istream >> std::ws >> steps;

  if (steps == "first")
  {
   return { bookmark,
        std::make_pair(details::UnionParameter::KEY_WORD, details::MoveParameter(BookInterface::KeyWord::FIRST)) };
  }

  if (steps == "last")
  {
    return { bookmark,
        std::make_pair(details::UnionParameter::KEY_WORD, details::MoveParameter(BookInterface::KeyWord::LAST)) };
  }

  int sign = 1;
  switch (steps[0])
  {
  case '+':
    steps.erase(0, 1);
    break;
  case '-':
    steps.erase(0, 1);
    sign = -1;
    break;
  }

  steps = checkNumber(steps);
  if (steps.empty())
  {
    std::cout << "<INVALID STEP>\n";
    return { bookmark,
      std::make_pair(details::UnionParameter::INVALID, details::MoveParameter(0)) };
  }
  return { bookmark,
    std::make_pair(details::UnionParameter::STEPS, details::MoveParameter(sign * std::stoi(steps))) };
}

void executeAdd(AddCommand& command, BookInterface& telephoneBookInterface)
{
  if (!command.note.first.empty() && !command.note.second.empty())
  {
    telephoneBookInterface.add(command.note);
  }
}

void executeStore(StoreCommand& command, BookInterface& telephoneBookInterface)
{
  if (!command.bookmark.empty() && !command.newBookmark.empty())
  {
    telephoneBookInterface.store(command.bookmark, command.newBookmark, std::cout);
  }
}

void executeInsert(InsertCommand& command, BookInterface& telephoneBookInterface)
{
  if (!command.bookmark.empty() && !command.position.empty()
    && !command.note.first.empty() && !command.note.second.empty())
  {
    if (command.position == "before")
    {
      telephoneBookInterface.insertBefore(command.bookmark, command.note, std::cout);
    }
    else if (command.position == "after")
    {
      telephoneBookInterface.insertAfter(command.bookmark, command.note, std::cout);
    }
  }
}

void executeDelete(DeleteCommand& command, BookInterface& telephoneBookInterface)
{
if (!command.bookmark.empty())
  {
    telephoneBookInterface.deleteNote(command.bookmark, std::cout);
  }
}

void executeShow(ShowCommand& command, BookInterface& telephoneBookInterface)
{
  if (!command.bookmark.empty())
  {
    telephoneBookInterface.show(command.bookmark, std::cout);
  }
}

void executeMove(MoveCommand& command, BookInterface& telephoneBookInterface)
{
  if (!command.bookmark.empty() && command.moveChoice.first == details::UnionParameter::KEY_WORD)
  {
    telephoneBookInterface.move(command.bookmark, command.moveChoice.second.keyWord, std::cout);
  }
  else if (!command.bookmark.empty() && command.moveChoice.first == details::UnionParameter::STEPS)
  {
    telephoneBookInterface.move(command.bookmark, command.moveChoice.second.steps, std::cout);
  }
}

void add(std::istream& istream, BookInterface& telephoneBookInterface)
{
  AddCommand adding = parseAdd(istream);
  executeAdd(adding, telephoneBookInterface);
}

void store(std::istream& istream, BookInterface& telephoneBookInterface)
{
  StoreCommand bookmarks = parseStore(istream);
  executeStore(bookmarks, telephoneBookInterface);
}

void insert(std::istream& istream, BookInterface& telephoneBookInterface)
{
  InsertCommand insertion = parseInsert(istream);
  executeInsert(insertion, telephoneBookInterface);
}

void deleteNote(std::istream& istream, BookInterface& telephoneBookInterface)
{
  DeleteCommand bookmark = parseDelete(istream);
  executeDelete(bookmark, telephoneBookInterface);
}

void show(std::istream& istream, BookInterface& telephoneBookInterface)
{
  ShowCommand bookmark = parseShow(istream);
  executeShow(bookmark, telephoneBookInterface);
}

void move(std::istream& istream, BookInterface& telephoneBookInterface)
{
  MoveCommand moving = parseMove(istream);
  executeMove(moving, telephoneBookInterface);
}
