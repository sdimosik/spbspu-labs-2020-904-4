#include "command.hpp"
#include "parse.hpp"

namespace command
{
  void addCommand(PhoneBookContainer &phoneBook, std::string &number, std::string &name)
  {
    phoneBook.add(PhoneBook::Note{number, name});
  }
  
  void storeCommand(PhoneBookContainer &phoneBook, std::string &bookmark, std::string &newBookmark)
  {
    phoneBook.storeBookmark(bookmark, newBookmark);
  }
  
  void insertCommand(PhoneBookContainer &phoneBook, std::string &direction, std::string &bookmark, std::string &number,
                     std::string &name)
  {
    PhoneBook::Note newNote{number, name};
    if (direction == "before")
    {
      phoneBook.insertBefore(bookmark, newNote);
    }
    else if (direction == "after")
    {
      phoneBook.insertAfter(bookmark, newNote);
    }
  }
  
  void eraseCommand(PhoneBookContainer &phoneBook, std::string &bookmark)
  {
    phoneBook.removeNote(bookmark);
  }
  
  void showCommand(PhoneBookContainer &phoneBook, std::string &bookmark)
  {
    phoneBook.showNote(bookmark);
  }
  
  void moveCommand(PhoneBookContainer &phoneBook, std::string &bookmark, std::string &steps)
  {
    if (steps == "first")
    {
      phoneBook.moveBookmark(bookmark, PhoneBook::MoveType::FIRST);
    }
    else if (steps == "last")
    {
      phoneBook.moveBookmark(bookmark, PhoneBook::MoveType::LAST);
    }
    else
    {
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
      
      if (!parse::isNumberValid(steps))
      {
        std::cout << parse::INVALID_STEP;
      }
      else
      {
        phoneBook.moveBookmark(bookmark, stoi(steps) * sign);
      }
    }
  }
  
  void exec(PhoneBookContainer &phoneBook, const std::string &command, std::string &direction,
            std::string &bookmark,
            std::string &newBookmark,
            std::string &number, std::string &name, std::string &steps)
  {
    if (command == "add")
    {
      addCommand(phoneBook, number, name);
    }
    else if (command == "store")
    {
      storeCommand(phoneBook, bookmark, newBookmark);
    }
    else if (command == "insert")
    {
      insertCommand(phoneBook, direction, bookmark, number, name);
    }
    else if (command == "delete")
    {
      eraseCommand(phoneBook, bookmark);
    }
    else if (command == "show")
    {
      showCommand(phoneBook, bookmark);
    }
    else if (command == "move")
    {
      moveCommand(phoneBook, bookmark, steps);
    }
  }
}
