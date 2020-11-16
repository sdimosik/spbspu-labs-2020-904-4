#ifndef B3_PHONEBOOKCONTAINER_HPP
#define B3_PHONEBOOKCONTAINER_HPP

#include <memory>
#include "phoneBook.hpp"

class PhoneBookContainer
{
public:
  
  PhoneBookContainer(std::unique_ptr<PhoneBook> &&book);
  
  using MoveType = PhoneBook::MoveType;
  
  static void show(PhoneBook::Iterator it);
  
  void add(const PhoneBook::Note &note);
  
  void insertBefore(const std::string &bookmark, const PhoneBook::Note &note);
  
  void insertAfter(const std::string &bookmark, const PhoneBook::Note &note);
  
  void removeNote(const std::string &bookmark);
  
  void showNote(const std::string &bookmark);
  
  void storeBookmark(const std::string &bookmark, const std::string &bookmarkNew);
  
  void moveBookmark(const std::string &bookmark, int steps);
  
  void moveBookmark(const std::string &bookmark, MoveType moveType);

private:
  std::unique_ptr<PhoneBook> book_;
  std::map<std::string, PhoneBook::Iterator> bookmarks_;
};


#endif //B3_PHONEBOOKCONTAINER_HPP
