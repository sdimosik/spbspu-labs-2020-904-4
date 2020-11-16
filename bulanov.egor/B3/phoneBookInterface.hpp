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

  void executeAdd(const PhoneBook::Records &record);

  void executeStore(const std::string &bookmark, const std::string &newBookmark);

  void executeInsertBefore(const std::string &bookmark, const PhoneBook::Records &record);

  void executeInsertAfter(const std::string &bookmark, const PhoneBook::Records &record);

  void executeRemove(const std::string &bookmark);

  void executeShow(const std::string &bookmark);

  void executeMove(const std::string &bookmark, const int step);

  void executeMove(const std::string &bookmark, const MovePosition &position);

private:
  std::unique_ptr<PhoneBook> phoneBook_;
  std::map<std::string, PhoneBook::iterator> bookmark_;
};

#endif
