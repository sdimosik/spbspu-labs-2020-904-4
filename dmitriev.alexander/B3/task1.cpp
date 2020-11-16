#include <iostream>
#include <sstream>
#include "phoneBook.hpp"
#include "dataUtills.hpp"
#include "phoneBookContainer.hpp"

const std::string INVALID_COMMAND = "<INVALID COMMAND>\n";
const std::string INVALID_STEP = "<INVALID STEP>\n";

void addCommand(PhoneBookContainer &phoneBook, std::istream &sin)
{
  std::string number;
  sin >> std::ws >> number;

  std::string name;
  std::getline(sin >> std::ws, name);

  if (!isNumberValid(number) || !refactorAndCheckName(name))
  {
    std::cout << INVALID_COMMAND;
    return;
  }

  phoneBook.addNote(PhoneBook::Note{number, name});
}


void storeCommand(PhoneBookContainer &phoneBook, std::istream &sin)
{
  std::string bookmark;
  sin >> std::ws >> bookmark;

  std::string newBookmark;
  sin >> std::ws >> newBookmark;

  if (!sin.eof() || !isBookmarkValid(bookmark) || !isBookmarkValid(newBookmark))
  {
    std::cout << INVALID_COMMAND;
  } else
  {
    phoneBook.storeBookmark(bookmark, newBookmark);
  }
}


void insertCommand(PhoneBookContainer &phoneBook, std::istream &sin)
{
  std::string direction;
  sin >> std::ws >> direction;

  std::string bookmark;
  sin >> std::ws >> bookmark;

  std::string number;
  sin >> std::ws >> number;

  std::string name;

  std::getline(sin >> std::ws, name);

  if (!isBookmarkValid(bookmark) || !isNumberValid(number) || !refactorAndCheckName(name))
  {
    std::cout << INVALID_COMMAND;
    return;
  }

  PhoneBook::Note newNote{number, name};
  if (direction == "before")
  {
    phoneBook.insertNoteBefore(bookmark, newNote);
  } else if (direction == "after")
  {
    phoneBook.insertNoteAfter(bookmark, newNote);
  } else
  {
    std::cout << INVALID_COMMAND;
  }
}


void eraseCommand(PhoneBookContainer &phoneBook, std::istream &sin)
{
  std::string bookmark;
  sin >> std::ws >> bookmark;

  if (!sin.eof() || !isBookmarkValid(bookmark))
  {
    std::cout << INVALID_COMMAND;
  } else
  {
    phoneBook.removeNote(bookmark);
  }
}


void showCommand(PhoneBookContainer &phoneBook, std::istream &sin)
{
  std::string bookmark;
  sin >> std::ws >> bookmark;

  if (!sin.eof() || !isBookmarkValid(bookmark))
  {
    std::cout << INVALID_COMMAND;
  } else
  {
    phoneBook.showNote(bookmark);
  }
}

void moveCommand(PhoneBookContainer &phoneBook, std::istream &sin)
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
  } else if (steps == "first")
  {
    phoneBook.moveBookmark(bookmark, PhoneBookContainer::MovePosition::FIRST);
  } else if (steps == "last")
  {
    phoneBook.moveBookmark(bookmark, PhoneBookContainer::MovePosition::LAST);
  } else
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
    } else if (steps[0] == '+')
    {
      steps.erase(steps.begin());
    }

    if (!isNumberValid(steps))
    {
      std::cout << INVALID_STEP;
    } else
    {
      phoneBook.moveBookmark(bookmark, stoi(steps) * sign);
    }
  }
}

void parseCommand(PhoneBookContainer &phoneBook, const std::string &command, std::istream &sin)
{
  if (command == "add")
  {
    addCommand(phoneBook, sin);
  } else if (command == "store")
  {
    storeCommand(phoneBook, sin);
  } else if (command == "insert")
  {
    insertCommand(phoneBook, sin);
  } else if (command == "delete")
  {
    eraseCommand(phoneBook, sin);
  } else if (command == "show")
  {
    showCommand(phoneBook, sin);
  } else if (command == "move")
  {
    moveCommand(phoneBook, sin);
  } else
  {
    std::cout << INVALID_COMMAND;
  }
}

void task1()
{
  PhoneBook book;
  PhoneBookContainer phoneBook(std::make_unique<PhoneBook>(book));
  std::string string;
  while (std::getline(std::cin, string))
  {
    std::stringstream sin(string);
    std::string command;
    sin >> command;
    parseCommand(phoneBook, command, sin);
  }

  if (!std::cin.eof() && !std::cin.good())
  {
    throw std::ios_base::failure("Error while reading data!\n");
  }
}
