#ifndef SPBSPU_LABS_2020_904_4_PHONEBOOKINTERFACE_HPP
#define SPBSPU_LABS_2020_904_4_PHONEBOOKINTERFACE_HPP

#include "phoneBook.hpp"
#include <iostream>
#include <map>
#include <memory>


class PhoneBookInterface
{
public:

  enum class MovePosition
  {
    FIRST,
    LAST
  };

  PhoneBookInterface(std::unique_ptr<PhoneBook> &&phoneBook);

  void add(const PhoneBook::PhoneBookNote &note);

  void store(const std::string &bookmark, const std::string &newBookmark);

  void insertAfter(const std::string &bookmark, const PhoneBook::PhoneBookNote &note);

  void insertBefore(const std::string &bookmark, const PhoneBook::PhoneBookNote &note);

  void deleteBookmarkNote(const std::string &bookmark);

  void showBookmark(const std::string &bookmark);

  void moveBookmark(const std::string &bookmark, const int step);

  void moveBookmark(const std::string &bookmark, const MovePosition &pos);

private:
  std::unique_ptr<PhoneBook> phoneBook_;
  std::map<std::string, PhoneBook::iterator> bookmarks_;

};

#endif
