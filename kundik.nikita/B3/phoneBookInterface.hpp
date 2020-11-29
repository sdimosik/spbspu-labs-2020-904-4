#ifndef PHONE_BOOK_INTERFACE_HPP
#define PHONE_BOOK_INTERFACE_HPP

#include <map>
#include <memory>
#include "phonebook.hpp"

class PhoneBookInterface
{
public:

  enum class MovePositionKeyWords
  {
    FIRST,
    LAST,
  };

  PhoneBookInterface(std::unique_ptr<PhoneBook>&& other);
  void addRecord(PhoneBook::Record& newRecord);
  void storeMark(const std::string& markName, const std::string& newMarkName);
  void insertBefore(PhoneBook::Record& newRecord, const std::string& markName);
  void insertAfter(PhoneBook::Record& newRecord, const std::string& markName);
  void deleteRecordOnMark(const std::string& markName);
  void showMark(const std::string& markName);
  void moveMark(const std::string& markName, int step);
  void moveMark(const std::string& markName, const MovePositionKeyWords& pos);

private:
  std::unique_ptr<PhoneBook> phoneBook_;
  std::map<std::string, PhoneBook::Iterator> bookMarks_;
};
#endif
