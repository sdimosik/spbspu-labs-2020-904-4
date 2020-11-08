#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <string>
#include <list>


class phoneBook
{
public:
  struct phoneNote
  {
    std::string number;
    std::string name;
  };
  using iterator = std::list<phoneNote>::iterator;

  iterator begin() noexcept;
  iterator end() noexcept;

  void insertAfter(const std::string &number, const std::string &name, iterator iter);
  void insertBefore(const std::string &number, const std::string &name, iterator iter);
  void replace(const std::string &name, const std::string &number, iterator iter);
  void pushBack(const std::string &name, const std::string &number);
  void eraseNote(iterator iter);
  iterator move(iterator iter, const int steps);

  void showCurrent(std::ostream &out, iterator iter) const;

private:
  std::list<phoneNote> list_;
};


#endif
