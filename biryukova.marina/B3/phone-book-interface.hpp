#ifndef PHONE_BOOK_INTERFACE_HPP
#define PHONE_BOOK_INTERFACE_HPP
#include <map>
#include <string>
#include <memory>
#include "phone-book.hpp"

const std::string CURRENT = "current";

class PhoneBookInterface
{
public:
  using IteratorType = PhoneBook::IteratorType;
  PhoneBookInterface(std::unique_ptr<PhoneBook>&& phonebook);
  PhoneBookInterface(const PhoneBookInterface& rhs) = default;
  ~PhoneBookInterface() = default;
  void move(const std::string& steps, std::ostream& errorOut, const std::string& bookmark = CURRENT);
  void insertAfter(const std::string& number, const std::string& name, std::ostream& errorOut, 
      const std::string& bookmark = CURRENT);
  void insertBefore(const std::string& number, const std::string& name, std::ostream& errorOut, 
      const std::string& bookmark = CURRENT);
  void insertToEnd(const std::string& number, const std::string& name);
  void deleteBookmark(const std::string& bookmark, std::ostream& errorOut);
  void addBookmark(const std::string& oldMark, const std::string& newMark, std::ostream& errorOut);
  void showBookmark(std::ostream& out, std::ostream& errorOut, const std::string& mark = CURRENT);
private:
  using BookmarksType = std::map<std::string, IteratorType>;
  std::unique_ptr<PhoneBook> phonebook_;
  BookmarksType bookmarks_;
  IteratorType getBookmarkIter(const std::string& bookmark);
};


#endif
