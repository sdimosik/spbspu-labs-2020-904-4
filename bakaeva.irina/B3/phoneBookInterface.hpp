#ifndef B3_PHONEBOOKINTERFACE_HPP
#define B3_PHONEBOOKINTERFACE_HPP

#include <iostream>
#include <map>
#include <memory>
#include "phoneBook.hpp"

class PhoneBookInterface
{
public:
  enum class MovePosition
  {
    FIRST,
    LAST
  };

  PhoneBookInterface(std::unique_ptr<PhoneBook>&& phoneBook);

  void addNote(const PhoneBook::Note &note);

  void storeBookmark(const std::string &bookmark,const  std::string &newBookmark);

  void insertNoteBefore(const std::string &bookmark, const PhoneBook::Note &note);

  void insertNoteAfter(const std::string &bookmark, const PhoneBook::Note &note);

  void eraseNote(const std::string &bookmark);

  void showNote(const std::string &bookmark);

  void moveBookmark(const std::string &bookmark, const int steps);

  void moveBookmark(const std::string &bookmark, const MovePosition &position);

private:
  std::unique_ptr<PhoneBook> phoneBook_;
  std::map<std::string, PhoneBook::iterator> bookmarks_;
};

#endif
