#ifndef B3_PHONEBOOK_HPP
#define B3_PHONEBOOK_HPP

#include <iostream>
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

  void showNote(iterator it) const;

  iterator next(iterator it);

  iterator prev(iterator it);

  iterator insertNoteBefore(iterator it, const Note &note);

  iterator insertNoteAfter(iterator it, const Note &note);

  iterator replaceNote(iterator it, const Note &note);

  void pushBack(const Note &note);

  iterator move(iterator it, const int steps);

  iterator erase(iterator it);

  iterator begin() noexcept;

  iterator end() noexcept;

private:
  std::list<Note> listOfNotes_;
};

#endif
