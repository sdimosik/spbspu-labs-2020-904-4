#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <iostream>
#include <map>
#include <list>

class PhoneBook
{
public:
  struct Note
  {
    std::string number_;
    std::string name_;
  };

  using iterator = std::list<Note>::iterator;

  iterator insertNote(iterator, const Note &);

  iterator removeAt(iterator);

  iterator beginIter();

  iterator endIter();

  void pushBack(const Note&);

  int size() const;

private:
  std::list<Note> noteList_;
};

#endif
