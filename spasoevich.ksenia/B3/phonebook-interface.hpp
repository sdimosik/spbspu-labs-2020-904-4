#ifndef PHONEBOOK_INTERFACE_HPP
#define PHONEBOOK_INTERFACE_HPP

#include <map>
#include <string>
#include <memory>
#include "phone-book.hpp"

class phoneBookInterface
{
public:
  using Iterator = phoneBook::Iterator;
  phoneBookInterface(std::unique_ptr<phoneBook>&& phonebook);
  void add(const std::string& oldMark, const std::string& newMark, std::ostream& error);
  void insertBefore(const std::string& number, const std::string& name, std::ostream& Error, const std::string& bookmark);
  void insertAfter(const std::string& number, const std::string& name, std::ostream& error, const std::string& bookmark = "current");
  void insertAtEnd(const std::string& number, const std::string& name);
  void deleteNote(const std::string& bookmark, std::ostream& error);
  void show(std::ostream& out, std::ostream& error, const std::string& mark = "current");
  void move(const std::string& steps, std::ostream& error, const std::string& bookmark = "current");
private:
  using BookmarksType=std::map<std::string, Iterator>;
  BookmarksType bookmarks;
  std::unique_ptr<phoneBook> PhoneBook;
  Iterator getBookmarkIter(const std::string& bookmark);
};

#endif
