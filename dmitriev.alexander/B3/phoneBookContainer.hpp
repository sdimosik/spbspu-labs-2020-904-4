#ifndef PHONEBOOKCONTAINER_HPP
#define PHONEBOOKCONTAINER_HPP

#include <map>
#include <string>
#include <memory>
#include "phoneBook.hpp"

class PhoneBookContainer
{
public:
  enum class MovePosition
  {
    FIRST,
    LAST
  };

  PhoneBookContainer(std::unique_ptr<PhoneBook>&&);

  static void showNote(PhoneBook::iterator);

  void addNote(const PhoneBook::Note &note);

  void insertNoteBefore(const std::string &, const PhoneBook::Note &);

  void insertNoteAfter(const std::string &, const PhoneBook::Note &);

  void removeNote(const std::string &);

  void showNote(const std::string &);

  void storeBookmark(const std::string &, const std::string &);

  void moveBookmark(const std::string &, int);

  void moveBookmark(const std::string &, MovePosition);

private:
  void insertNote(PhoneBook::iterator,
    std::map<std::string, PhoneBook::iterator>::const_iterator, const PhoneBook::Note &);

  std::map<std::string, PhoneBook::iterator> bookmarksMap_;
  std::unique_ptr<PhoneBook> book_;
};

#endif
