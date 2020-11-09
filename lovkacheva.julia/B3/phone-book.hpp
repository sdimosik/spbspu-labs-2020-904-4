#ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP
#include <list>
#include <string>
#include <iostream>

namespace lovkacheva
{
  class PhoneBook
  {
  public:
    struct entry_t
    {
      std::string name_;
      std::string number_;
    };
    using iterator = std::list<entry_t>::iterator;
    void show(const iterator& it, std::ostream& out = std::cout) const;
    iterator insertBefore(const iterator& it, std::string name, std::string number);
    iterator insertAfter(const iterator& it, std::string name, std::string number);
    iterator insertBack(std::string name, std::string number);
    void erase(iterator& it);
    iterator begin();
    iterator end();
    bool empty() const;
    std::list<entry_t>::size_type size() const;

  private:
    std::list<entry_t> contents_;
  };
}
#endif
