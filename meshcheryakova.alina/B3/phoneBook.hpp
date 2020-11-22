#ifndef B3_PHONEBOOK_HPP
#define B3_PHONEBOOK_HPP

#include<iostream>
#include <list>


class phoneBook
{
public:
  struct contact_str
  {
    std::string name;
    std::string number;
  };

  using book_list = std::list<contact_str>;
  using value_type = book_list::value_type;
  using iterator = book_list::iterator;

  iterator begin() { return book_.begin(); };
  iterator end() { return book_.end(); };
  void push_back (const contact_str& contact) { book_.push_back(contact); };
  iterator insert (iterator pos, const value_type value) { return book_.insert(pos, value); };
  iterator erase (iterator pos) { return book_.erase(pos); };
  bool empty() const noexcept { return book_.empty(); }

private:
book_list book_;
};

#endif //B3_PHONEBOOK_HPP
