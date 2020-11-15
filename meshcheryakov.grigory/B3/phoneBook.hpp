#ifndef SPBSPU_LABS_2020_904_4_PHONEBOOK_HPP
#define SPBSPU_LABS_2020_904_4_PHONEBOOK_HPP

#include <list>
#include <iostream>

class PhoneBook
{
public:
  struct PhoneBookNote
  {
    std::string number_;
    std::string name_;
  };

  using iterator = std::list<PhoneBookNote>::iterator;

  void show(iterator it) const;

  iterator prev(iterator it);

  iterator insertAfter(iterator it, const PhoneBookNote &note);

  iterator insertBefore(iterator it, const PhoneBookNote &note);

  void pushBack(const PhoneBookNote &note);

  iterator move(iterator it, const int step);

  iterator deleteBookmark(iterator it);

  iterator begin() noexcept;

  iterator end() noexcept;

private:
  std::list<PhoneBookNote> noteList_;
};

#endif
