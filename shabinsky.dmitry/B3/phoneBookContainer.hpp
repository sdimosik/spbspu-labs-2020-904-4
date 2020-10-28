#ifndef B3_PHONEBOOKCONTAINER_HPP
#define B3_PHONEBOOKCONTAINER_HPP

#include "phoneBook.hpp"

class phoneBookContainer
{
public:
  
  using InsertType = PhoneBook::InsertType;
  
  using MoveType = PhoneBook::MoveType;
  
  phoneBookContainer();
  
  void add(const PhoneBook::Note &note);
  
  void insert(const std::string &bookmark, const InsertType &insertType, const PhoneBook::Note &note);
  
  void removeNote(const std::string &bookmark);
  
  void showNote(const std::string &bookmark);
  
  void storeBookmark(const std::string &bookmark, const std::string &bookmarkNew);
  
  void moveBookmark(const std::string &bookmark, int steps);
  
  void moveBookmark(const std::string &bookmark, const MoveType &moveType);

private:
  PhoneBook book_;
  std::map<std::string, PhoneBook::Iterator> bookmarks_;
};


#endif //B3_PHONEBOOKCONTAINER_HPP
