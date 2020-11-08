#ifndef PHONEBOOKINTERFACE_HPP
#define PHONEBOOKINTERFACE_HPP

#include <iostream>
#include <memory>
#include <map>

#include "phoneBook.hpp"

class phoneBookInterface
{
public:
  enum class position
  {
    FIRST,
    LAST
  };

  phoneBookInterface(std::unique_ptr<phoneBook>&& phoneBook);

  void addNote(const phoneBook::phoneNote &note);
  void storeBookmark(const std::string &bookmark,const  std::string &newBookmark);

  void insertBefore(const std::string &bookmark, const phoneBook::phoneNote &note);
  void insertAfter(const std::string &bookmark, const phoneBook::phoneNote &note);
  void eraseNote(const std::string &bookmark);
  void showNote(std::ostream &out, const std::string &bookmark);
  void moveBookmark(const std::string &bookmark, const int steps);
  void moveBookmark(const std::string &bookmark, const position &position);

private:
  std::unique_ptr<phoneBook> phoneBook_;
  std::map<std::string, phoneBook::iterator> marks_;
};


#endif
