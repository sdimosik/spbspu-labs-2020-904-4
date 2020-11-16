#ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP

#include <string>
#include <list>

class PhoneBook
{
public:
  struct Record
  {
    std::string number;
    std::string name;
  };
  using Iterator = std::list<Record>::iterator;

  void showNote(Iterator it);
  Iterator insertBefore(Record& record, Iterator it);
  Iterator insertAfter(Record& record, Iterator it);
  void insertInTheEnd(Record& record);
  Iterator deleteRecord(Iterator it);
  Iterator getBegin();
  Iterator getEnd();

private:
  std::list<Record> listOfRecords_;
};

#endif
